"""Generate the static project page and bilingual lessons from repository content."""
from html import escape
from pathlib import Path
import re
import shutil

ROOT = Path(__file__).resolve().parent.parent
OUTPUT = ROOT / 'build/project-page'


def read_lesson(path):
    text = path.read_text(encoding='utf-8')
    metadata = {}
    if text.startswith('---\n'):
        header, text = text[4:].split('---\n', 1)
        metadata = dict(line.split(':', 1) for line in header.splitlines() if ':' in line)
        metadata = {key: value.strip() for key, value in metadata.items()}
    return metadata, text.strip()


def inline(text):
    # Escape source HTML and handle only the inline syntax used by these lessons.
    tokens = re.split(r'(`[^`]+`|\*\*.+?\*\*)', text)
    result = []
    for token in tokens:
        if token.startswith('`') and token.endswith('`'):
            result.append(f'<code>{escape(token[1:-1])}</code>')
        elif token.startswith('**') and token.endswith('**'):
            result.append(f'<strong>{escape(token[2:-2])}</strong>')
        else:
            result.append(escape(token))
    return ''.join(result)


def render_lesson(text, folder, language):
    lines = text.splitlines()
    rendered = []
    position = 0
    labels = {'en': {'code': 'Example', 'exercise': 'Exercise starter', 'solution': 'show solution'},
              'ko': {'code': '예제', 'exercise': '연습 문제 코드', 'solution': '풀이 보기'}}[language]
    while position < len(lines):
        line = lines[position]
        if not line.strip():
            position += 1
            continue
        if line.startswith('```'):
            code = []
            position += 1
            while position < len(lines) and not lines[position].startswith('```'):
                code.append(lines[position])
                position += 1
            if position == len(lines):
                raise ValueError(f'Unclosed code block in {folder}')
            rendered.append('<pre><code>' + escape('\n'.join(code)) + '</code></pre>')
        elif line.startswith('@'):
            kind, filename = line[1:].split(maxsplit=1)
            if kind not in labels or Path(filename).name != filename:
                raise ValueError(f'Unsupported lesson directive: {line}')
            code = escape((folder / filename).read_text(encoding='utf-8'))
            block = f'<pre><code>{code}</code></pre>'
            if kind == 'solution':
                rendered.append(f'<details><summary>{labels[kind]}</summary>{block}</details>')
            else:
                rendered.append(f'<div class="code-label">{labels[kind]} · {escape(filename)}</div>{block}')
        elif match := re.match(r'^(#{1,6}) (.+)$', line):
            level = max(2, len(match[1]))
            rendered.append(f'<h{level}>{inline(match[2])}</h{level}>')
        elif match := re.fullmatch(r'!\[([^\]]*)\]\(([^)]+)\)', line.strip()):
            image = Path(match[2])
            if image.is_absolute() or '..' in image.parts or not (folder / image).is_file():
                raise ValueError(f'Missing or unsafe lesson image: {line}')
            source = f'{folder.name}/{image.as_posix()}'
            rendered.append(f'<figure class="lesson-screenshot"><img src="{escape(source, quote=True)}" '
                            f'alt="{escape(match[1], quote=True)}" loading="lazy">'
                            f'<figcaption>{escape(match[1])}</figcaption></figure>')
        elif re.match(r'^[-*] ', line):
            items = []
            while position < len(lines) and re.match(r'^[-*] ', lines[position]):
                items.append('<li>' + inline(lines[position][2:]) + '</li>')
                position += 1
            rendered.append('<ul>' + ''.join(items) + '</ul>')
            continue
        else:
            paragraph = [line]
            position += 1
            while position < len(lines) and lines[position].strip() and not re.match(r'^(#|@|```|[-*] )', lines[position]):
                paragraph.append(lines[position])
                position += 1
            rendered.append('<p>' + inline(' '.join(paragraph)) + '</p>')
            continue
        position += 1
    return '\n'.join(rendered)


def page(title, language, content, switch_link):
    home, lessons, switch = ('Home', 'Lessons', '한국어') if language == 'en' else ('홈', '레슨', 'English')
    return f'''<!doctype html>
<html lang="{language}"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<title>{escape(title)} — Small C++</title><link rel="icon" href="../../assets/smallcpp_128.png">
<link rel="stylesheet" href="../../style.css?v=0.76.16"></head><body>
<header class="navigation wrap"><a class="brand" href="../../index.html">Small C++<span class="brand-dot">.</span></a>
<nav aria-label="Navigation"><a href="../../index.html">{home}</a><a href="index.html">{lessons}</a></nav>
<a class="language" href="{switch_link}">{switch}</a></header>
<main class="reader wrap">{content}</main>
<footer class="wrap"><span>Small C++</span><a href="https://github.com/sodomau/small-cpp/blob/main/LICENSE">Licensed under MIT</a></footer>
</body></html>'''


def build():
    OUTPUT.mkdir(parents=True, exist_ok=True)
    for name in ('index.html', 'style.css', 'app.js'):
        shutil.copy2(ROOT / 'site' / name, OUTPUT / name)
    assets = OUTPUT / 'assets'
    assets.mkdir(exist_ok=True)
    for source in (ROOT / 'ide/assets/smallcpp_128.png', ROOT / 'docs/images/ide-dark.png', ROOT / 'docs/images/ide-light.png'):
        shutil.copy2(source, assets / source.name)
    lessons = [(folder.name, folder) for folder in sorted((ROOT / 'tutorial').iterdir()) if folder.is_dir()]
    core_count = len(lessons)
    lessons += [('image-' + folder.name, folder) for folder in sorted((ROOT / 'extensions/image/tutorial').iterdir()) if folder.is_dir()]
    image_count = len(lessons) - core_count
    homepage = OUTPUT / 'index.html'
    text = homepage.read_text(encoding='utf-8')
    text = re.sub(r'(<strong data-core-lesson-count>)\d+(</strong>)',
                  lambda match: match[1] + str(core_count) + match[2], text)
    text = re.sub(r'\d+ core lessons', f'{core_count} core lessons', text)
    text = re.sub(r'핵심 \d+개', f'핵심 {core_count}개', text)
    text = re.sub(r'plus \d+ Image extension lessons', f'plus {image_count} Image extension lessons', text)
    text = re.sub(r'Image 확장 \d+개', f'Image 확장 {image_count}개', text)
    homepage.write_text(text, encoding='utf-8', newline='\n')
    for language, other in (('en', 'ko'), ('ko', 'en')):
        destination = OUTPUT / 'lessons' / language
        destination.mkdir(parents=True, exist_ok=True)
        sections = {}
        for number, (slug, folder) in enumerate(lessons):
            metadata, text = read_lesson(folder / f'{language}.md')
            for reference in re.findall(r'!\[[^\]]*\]\(([^)]+)\)', text):
                image = Path(reference)
                if image.is_absolute() or '..' in image.parts or not (folder / image).is_file():
                    raise ValueError(f'Missing or unsafe lesson image: {reference}')
                target = destination / folder.name / image
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(folder / image, target)
            title = metadata.get('title', slug)
            subtitle = metadata.get('part-title', 'Image extension' if language == 'en' else 'Image 확장')
            part = metadata.get('part', 'image' if slug.startswith('image-') else 'core')
            section = sections.setdefault(part, {'title': subtitle, 'items': [], 'first': number + 1})
            section['items'].append(f'<li><a href="{slug}.html"><span>{number + 1:02}</span>{escape(title)}</a></li>')
            content = f'<p class="eyebrow">{escape(subtitle)}</p><h1>{escape(title)}</h1>'
            if goal := metadata.get('goal'):
                content += f'<p class="lesson-goal">{escape(goal)}</p>'
            content += render_lesson(text, folder, language)
            navigation = []
            if number:
                label = 'Previous lesson' if language == 'en' else '이전 레슨'
                navigation.append(f'<a class="button secondary" href="{lessons[number - 1][0]}.html">← {label}</a>')
            if number + 1 < len(lessons):
                label = 'Next lesson' if language == 'en' else '다음 레슨'
                navigation.append(f'<a class="button secondary" href="{lessons[number + 1][0]}.html">{label} →</a>')
            content += '<div class="lesson-navigation">' + ''.join(navigation) + '</div>'
            (destination / f'{slug}.html').write_text(page(title, language, content, f'../{other}/{slug}.html'), encoding='utf-8', newline='\n')
        title = 'One small step at a time.' if language == 'en' else '한 걸음씩, 차근차근.'
        description = (f'{core_count} core lessons + {image_count} Image lessons. Read, try the examples in the desktop IDE, and make them your own.'
                       if language == 'en' else f'핵심 {core_count}개 레슨과 Image 확장 {image_count}개 레슨. 설명을 읽고 데스크톱 IDE에서 예제를 실행하며 나만의 코드로 바꿔 보세요.')
        instruction = 'Choose a part to explore its lessons.' if language == 'en' else '배우고 싶은 파트를 눌러 레슨을 펼쳐 보세요.'
        content = f'<p class="eyebrow">SMALL STEPS</p><h1>{title}</h1><p class="lesson-goal">{description}</p><p>{instruction}</p>'
        for part, section in sections.items():
            count = len(section['items'])
            count_label = f'{count} lessons' if language == 'en' else f'{count}개 레슨'
            first, last = section['first'], section['first'] + count - 1
            content += (f'<details class="lesson-section" id="part-{escape(part, quote=True)}">'
                        f'<summary><span class="lesson-section-title">{escape(section["title"])}</span>'
                        f'<span class="lesson-section-count">{first:02}–{last:02} · {count_label}</span></summary>'
                        f'<ol class="lesson-index" start="{first}">' + ''.join(section['items']) + '</ol></details>')
        (destination / 'index.html').write_text(page(title, language, content, f'../{other}/index.html'), encoding='utf-8', newline='\n')
    return OUTPUT


if __name__ == '__main__':
    print(build())
