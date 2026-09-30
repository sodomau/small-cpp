#!/usr/bin/env python3
"""Validate the embedded curriculum and optionally compile/run its C++ programs.

No third-party Python packages. Without Qt, --compiler tests lesson output with
console routines extracted verbatim from small_runtime.cpp, NOT the GUI runtime.
The full-runtime link target is `small_tutorial_programs` in the Qt CMake project.
"""
from __future__ import annotations
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'tutorial'


def require(ok: bool, message: str) -> None:
    if not ok:
        raise ValueError(message)


def load_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding='utf-8'))


def validate() -> tuple[dict, list[Path]]:
    catalog = load_json(BASE / 'catalog.json')
    examples = {item['id'] for item in load_json(ROOT / 'examples/catalog.json')['examples']}
    require(catalog['version'] == 1 and catalog['totalLessons'] == 36, 'Unexpected curriculum format')
    require(len(catalog['parts']) == 6, 'Curriculum v2 must retain its six parts')
    ids: set[str] = set()
    resources: set[str] = {'catalog.json'}
    sources: list[Path] = []
    published = exercises = number = 0
    for part in catalog['parts']:
        for item in part['lessons']:
            number += 1
            require(item['number'] == number, 'Lesson numbers must be consecutive')
            require(item['id'] not in ids, 'Duplicate lesson id')
            ids.add(item['id'])
            require(bool(item['title'].strip()), 'Empty lesson title')
            name = item.get('source')
            if not name:
                continue
            require(bool(re.fullmatch(r'\d{2}_[a-z0-9_]+/lesson\.json', name)), f'Bad path: {name}')
            resources.add(name)
            path = BASE / name
            manifest = load_json(path)
            published += 1
            require(manifest['id'] == item['id'] and manifest['goal'].strip(), f'Bad lesson: {name}')
            require(len(manifest['exercises']) == 2, f'Exactly two exercises required: {name}')
            require(manifest.get('relatedExample', '') in examples, f'Unknown example in {name}')

            def check(local: str, extension: str) -> str:
                require(bool(re.fullmatch(r'[a-z0-9_]+\.' + extension, local)), f'Bad local path: {local}')
                file = path.parent / local
                text = file.read_text(encoding='utf-8')
                require(bool(text.strip()), f'Empty file: {file}')
                resources.add(file.relative_to(BASE).as_posix())
                if extension == 'cpp':
                    lesson_number = int(path.parent.name.split('_', 1)[0])
                    if lesson_number < 35:
                        require(len(re.findall(r'\bvoid\s+SmallMain\s*\(\s*\)', text)) == 1,
                                f'Each Try before Lesson 35 must be a complete SmallMain program: {file}')
                        require(not re.search(r'\bint\s+main\s*\(', text), f'Unexpected native main before Lesson 35: {file}')
                    else:
                        require(len(re.findall(r'\bint\s+main\s*\(', text)) == 1,
                                f'Lessons 35-36 must use a real main program: {file}')
                    sources.append(file)
                else:
                    # The initial renderer has no images, HTML, URLs or code
                    # fences; every executable code block has its own .cpp.
                    prose_without_inline_code = re.sub(r'`[^`]*`', '', text)
                    require('```' not in text and
                            not re.search(r'<[A-Za-z/][^>]*>|!\[|https?://', prose_without_inline_code),
                            f'Unsupported prose content: {file}')
                return text

            for block in manifest['blocks']:
                require(block['type'] in {'code', 'text'}, 'Unknown block type')
                check(block['source'], 'cpp' if block['type'] == 'code' else 'md')
            for exercise in manifest['exercises']:
                exercises += 1
                require(bool(exercise['title'].strip()), 'Missing exercise title')
                for key in ['prompt', 'hint']:
                    check(exercise[key], 'md')
                for key in ['starter', 'solution']:
                    check(exercise[key], 'cpp')
    require(number == 36 and published >= 5 and exercises == published * 2,
            'Published lessons must each have exactly two exercises')
    require(catalog['parts'][3]['lessons'][0]['id'] == 'text_files' and
            catalog['parts'][3]['lessons'][1]['id'] == 'binary_files', 'File lessons must stay in Part IV')
    require(len(sources) == len(set(sources)), 'Code sources must have distinct identities')
    qrc = ET.parse(ROOT / 'ide/SmallTutorials.qrc').getroot()
    aliases: list[str] = []
    for resource in qrc.findall('qresource'):
        require(resource.attrib['prefix'] == '/small/tutorial', 'Unexpected resource prefix')
        for entry in resource.findall('file'):
            alias = entry.attrib['alias']
            aliases.append(alias)
            actual = (ROOT / 'ide' / (entry.text or '')).resolve()
            require(actual == (BASE / alias).resolve() and actual.is_file(), f'Broken resource: {alias}')
    require(len(aliases) == len(set(aliases)), 'Duplicate resource alias')
    require(set(aliases) == resources, 'Tutorial qrc and content manifests differ')
    cases = load_json(ROOT / 'tests/tutorial_cases.json')['cases']
    covered = {case['source'] for case in cases}
    source_names = {p.relative_to(BASE).as_posix() for p in sources}
    console_sources = {name for name in source_names if int(name.split('_', 1)[0]) <= 9}
    require(covered == console_sources,
            'Every console tutorial program (Lessons 1-9) needs an output test')
    return {'lessons': number, 'published': published, 'exercises': exercises,
            'cppSources': len(sources), 'resourceFiles': len(resources), 'outputCases': len(cases)}, sources


def console_test_support() -> str:
    # Reuse the actual implementation under test, rather than reimplementing
    # Input semantics in a permissive fake. Qt drawing/event/audio code is not linked.
    runtime = (ROOT / 'runtime/small_runtime.cpp').read_text(encoding='utf-8')
    console_start = runtime.index('namespace small_detail')
    console_end = runtime.index('\nnamespace\n{', console_start)
    console = runtime[console_start:console_end]
    helpers = runtime[runtime.index('std::string ReadLine()'):runtime.index('QColor ToQt')]
    inputs = runtime[runtime.index('String Input()'):runtime.index('void Color::SetRGB')]
    return '''#include "small.h"
#include <iostream>
#include <sstream>
#include <locale>
#include <cmath>
namespace Small {
''' + console + '\nnamespace {\n' + helpers + '}\n' + inputs + '''
}
int main() {
    try { SmallMain(); return 0; }
    catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << '\\n'; return 1;
    }
}
'''


def compile_and_run(compiler: str, sources: list[Path]) -> dict:
    executable = shutil.which(compiler)
    require(executable is not None, f'Compiler not found: {compiler}')
    cases = load_json(ROOT / 'tests/tutorial_cases.json')['cases']
    flags = ['-std=c++20', '-DSMALL_BEGINNER_MODE', '-O0', '-g0',
             '-Wall', '-Wextra', '-Werror=parentheses', '-I', str(ROOT / 'runtime')]
    records = []
    with tempfile.TemporaryDirectory(prefix='small-tutorial-tests-') as temporary:
        work = Path(temporary)
        support = work / 'console_support.cpp'
        support.write_text(console_test_support(), encoding='utf-8')
        support_object = work / 'console_support.o'
        subprocess.run([executable, *flags, '-c', str(support), '-o', str(support_object)],
                       check=True, capture_output=True, text=True, timeout=45)
        for index, source in enumerate(sources):
            name = source.relative_to(BASE).as_posix()
            binary = work / (f'lesson_{index}' + ('.exe' if os.name == 'nt' else ''))
            result = subprocess.run([executable, *flags, '-include', str(ROOT / 'runtime/small.h'),
                                     str(source), str(support_object), '-o', str(binary)],
                                    capture_output=True, text=True, timeout=45)
            require(result.returncode == 0, f'Compile failed: {name}\n{result.stderr}')
            passed = 0
            for case in cases:
                if case['source'] != name:
                    continue
                run = subprocess.run([str(binary)], input=case['stdin'], capture_output=True,
                                     text=True, encoding='utf-8', cwd=work, timeout=5)
                require(run.returncode == case['exitCode'] and run.stdout == case['stdout'] and
                        run.stderr == case['stderr'],
                        f'Output mismatch: {name}/{case["name"]}\n'
                        f'code={run.returncode}, stdout={run.stdout!r}, stderr={run.stderr!r}')
                passed += 1
            records.append({'source': name, 'sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
                            'outputCasesPassed': passed, 'compilerWarnings': result.stderr})
    return {'compiler': executable, 'programsCompiledLinked': len(records),
            'outputCasesPassed': sum(r['outputCasesPassed'] for r in records),
            'scope': 'Console routines extracted verbatim from runtime; no Qt GUI/backend execution',
            'records': records}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', help='Also compile and run all content (g++ or clang++)')
    parser.add_argument('--report', type=Path, help='Optional JSON report file')
    args = parser.parse_args()
    counts, sources = validate()
    report: dict = {'content': counts}
    print('Tutorial content OK:', counts)
    if args.compiler:
        report['execution'] = compile_and_run(args.compiler, sources)
        print(f'{report["execution"]["programsCompiledLinked"]} programs compiled/linked; '
              f'{report["execution"]["outputCasesPassed"]} output cases passed with {args.compiler}')
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')


if __name__ == '__main__':
    main()
