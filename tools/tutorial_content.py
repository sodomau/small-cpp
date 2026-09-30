"""Validate filesystem-backed lesson packs without assuming a curriculum edition."""
from pathlib import Path
import re


def require(condition, message):
    if not condition:
        raise ValueError(message)


def validate_pack(base, languages, default, example_ids=None, core=True):
    lessons, sources, ids, numbers = [], set(), set(), set()
    for folder in sorted(p for p in Path(base).iterdir() if p.is_dir()):
        match = re.fullmatch(r'(\d{2})_([a-z][a-z0-9_]*)', folder.name)
        require(match is not None, f'Invalid lesson folder: {folder}')
        number, lesson_id = int(match[1]), match[2]
        require(number > 0 and number not in numbers and lesson_id not in ids,
                f'Duplicate lesson number or id: {folder}')
        numbers.add(number)
        ids.add(lesson_id)
        variants = []
        for language in languages:
            path = folder / f'{language}.md'
            if not path.exists():
                path = folder / f'{default}.md'
            require(path.is_file(), f'Missing lesson/default translation: {folder}')
            text = path.read_text(encoding='utf-8')
            require(text.startswith('---\n') and '\n---\n' in text[4:], f'Invalid front matter: {path}')
            front, body = text[4:].split('\n---\n', 1)
            meta = {}
            for line in front.splitlines():
                require(':' in line, f'Invalid metadata line: {path}')
                key, value = line.split(':', 1)
                require(key.strip() not in meta, f'Duplicate metadata key: {path}')
                meta[key.strip()] = value.strip()
            for key in (('title', 'goal', 'part', 'part-title') if core else ('title', 'goal')):
                require(bool(meta.get(key)), f'Missing {key}: {path}')
            related = meta.get('related-example', '')
            require(not related or example_ids is None or related in example_ids,
                    f'Unknown related example {related}: {path}')
            code_count = exercises = solutions = 0
            current_exercise = False
            fence = None
            for line in body.splitlines():
                stripped = line.strip()
                if stripped.startswith(('```', '~~~')):
                    marker = stripped[:3]
                    fence = None if fence == marker else marker
                    continue
                if fence:
                    continue
                if stripped.startswith('@'):
                    tag = re.fullmatch(r'@(code|exercise|solution)\s+([A-Za-z0-9_-]+\.cpp)', stripped)
                    require(tag is not None, f'Invalid code directive: {path}: {stripped}')
                    kind, filename = tag.groups()
                    source = folder / filename
                    require(source.is_file() and source.read_text(encoding='utf-8').strip(), f'Missing/empty source: {source}')
                    sources.add(source)
                    if kind == 'code':
                        require(not current_exercise, f'Exercise has no solution: {path}')
                        code_count += 1
                    elif kind == 'exercise':
                        require(not current_exercise, f'Exercise has no solution: {path}')
                        current_exercise = True
                        exercises += 1
                    else:
                        require(current_exercise, f'Orphan/duplicate solution: {path}')
                        current_exercise = False
                        solutions += 1
                for image in re.findall(r'!\[[^\]]*\]\(([^)]+)\)', line):
                    local = Path(image)
                    require(not local.is_absolute() and '..' not in local.parts and (folder / local).is_file(),
                            f'Missing/unsafe local image: {path}: {image}')
            require(fence is None, f'Unterminated code fence: {path}')
            require(code_count > 0 and exercises > 0 and not current_exercise and exercises == solutions,
                    f'Incomplete lesson examples/exercises: {path}')
            variants.append({'language': language, 'path': path, 'meta': meta,
                             'examples': code_count, 'exercises': exercises})
        lessons.append({'id': lesson_id, 'number': number, 'variants': variants})
    require(bool(lessons), f'No lessons: {base}')
    require(sorted(numbers) == list(range(1, len(numbers) + 1)), f'Nonconsecutive lesson numbers: {base}')
    return lessons, sorted(sources)
