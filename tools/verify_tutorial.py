#!/usr/bin/env python3
"""Validate external lesson packs. Optional checks use the actual Small runtime."""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
from tutorial_content import require, validate_pack

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'tutorial'

def validate():
    languages = json.loads((BASE / 'languages.json').read_text(encoding='utf-8'))
    require(languages['default'] in languages['languages'], 'Unknown default tutorial language')
    examples = {item['id'] for item in json.loads((ROOT / 'examples/catalog.json').read_text(encoding='utf-8'))['examples']}
    lessons, sources = validate_pack(BASE, languages['languages'], languages['default'], examples)
    cases = json.loads((ROOT / 'tests/tutorial_cases.json').read_text(encoding='utf-8'))
    require(cases['version'] == 2 and bool(cases['cases']), 'Missing current output fixtures')
    source_names = {source.relative_to(BASE).as_posix() for source in sources}
    for case in cases['cases']:
        require(case['source'] in source_names, f'Obsolete output fixture: {case["source"]}')
    return {'lessons': len(lessons), 'published': len(lessons),
            'exercises': sum(lesson['variants'][0]['exercises'] for lesson in lessons),
            'cppSources': len(sources), 'outputCases': len(cases['cases']),
            'languages': list(languages['languages'])}, sources

def syntax_check(compiler, sources):
    executable = shutil.which(compiler)
    require(executable is not None, f'Compiler not found: {compiler}')
    for source in sources:
        result = subprocess.run([executable, '-std=c++20', '-DSMALL_BEGINNER_MODE',
                                 '-include', str(ROOT / 'runtime/small.h'),
                                 '-fsyntax-only', str(source)], capture_output=True,
                                text=True, encoding='utf-8', errors='replace', timeout=45)
        require(result.returncode == 0, f'Syntax check failed: {source}\n{result.stderr}')
    return {'programsSyntaxChecked': len(sources), 'compiler': executable}

def real_runtime_checks(build_dir, cmake):
    build_dir = build_dir.resolve()
    subprocess.run([cmake, '--build', str(build_dir), '--target', 'small_tutorial_programs',
                    '--parallel', '4'], check=True)
    cases = json.loads((ROOT / 'tests/tutorial_cases.json').read_text(encoding='utf-8'))['cases']
    passed = 0
    for case in cases:
        source = Path(case['source'])
        name = 'small_tutorial_' + source.parent.name + '_' + source.stem
        if os.name == 'nt':
            name += '.exe'
        candidates = list((build_dir / 'bin').glob('**/tutorial/' + name))
        require(len(candidates) == 1, f'Expected one tutorial binary for {source}, found {len(candidates)}')
        binary = candidates[0]
        environment = dict(os.environ, QT_QPA_PLATFORM='offscreen', SMALL_TEST_NO_CONSOLE_PAUSE='1')
        environment['PATH'] = str(binary.parent.parent) + os.pathsep + environment.get('PATH', '')
        run = subprocess.run([str(binary)], input=case['stdin'], capture_output=True,
                             text=True, encoding='utf-8', errors='replace',
                             cwd=binary.parent.parent, env=environment, timeout=10)
        require(run.returncode == case['exitCode'] and run.stdout == case['stdout'] and run.stderr == case['stderr'],
                f'Output mismatch: {source}: exit={run.returncode}, stdout={run.stdout!r}, stderr={run.stderr!r}')
        passed += 1
    return {'realRuntimeOutputCasesPassed': passed, 'scope': 'Representative console fixtures; no GUI automation'}

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', help='Syntax-check all core C++ files')
    parser.add_argument('--build-dir', type=Path, help='Build all tutorial programs and run real-runtime console fixtures')
    parser.add_argument('--cmake', default='cmake')
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    counts, sources = validate()
    report = {'content': counts}
    print('Tutorial content OK:', counts)
    if args.compiler:
        report['syntax'] = syntax_check(args.compiler, sources)
        print(report['syntax'])
    if args.build_dir:
        report['execution'] = real_runtime_checks(args.build_dir, args.cmake)
        print(report['execution'])
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n', encoding='utf-8')

if __name__ == '__main__':
    main()
