"""Require real English coverage and matching runnable assets in both languages."""
from pathlib import Path
import re
from tutorial_content import validate_pack

root = Path(__file__).resolve().parents[1]
count = 0
for base, core in [(root / 'tutorial', True), (root / 'extensions/image/tutorial', False)]:
    lessons, _ = validate_pack(base, ['ko', 'en'], 'ko', core=core)
    for lesson in lessons:
        korean, english = [v['path'] for v in lesson['variants']]
        assert english.name == 'en.md', f'English silently falls back: {english}'
        ko, en = [p.read_text(encoding='utf-8') for p in [korean, english]]
        assert not re.search('[가-힣]', en), f'Untranslated text: {english}'
        assert re.findall(r'^@(code|exercise|solution)\s+(.+)$', ko, re.M) == re.findall(
            r'^@(code|exercise|solution)\s+(.+)$', en, re.M), f'Runnable asset mismatch: {english}'
        assert re.findall(r'```[^\n]*\n.*?```', ko, re.S) == re.findall(
            r'```[^\n]*\n.*?```', en, re.S), f'Example/output mismatch: {english}'
        count += 1
assert count == 100, f'Expected 97 core and 3 Image lessons, found {count}'
print('English coverage: 97 core + 3 Image lessons; matching examples and exercises.')
