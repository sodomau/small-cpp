"""Keep the multi-file tutorial listings aligned with runnable project samples."""
from pathlib import Path

root = Path(__file__).resolve().parents[1]
for sample, lesson in [('Greeting', '94_project_headers'), ('ScoreCard', '95_project_roles')]:
    folder = root / 'examples/projects' / sample
    sources = list(folder.glob('*.cpp'))
    assert len(sources) == 2 and len(list(folder.glob('*.h'))) == 1
    for language in ['ko', 'en']:
        prose = (root / 'tutorial' / lesson / (language + '.md')).read_text(encoding='utf-8')
        for file in folder.iterdir():
            text = file.read_text(encoding='utf-8')
            assert f'### {file.name}\n```cpp\n{text}```' in prose, (sample, language, file.name)
print('Project tutorial listings match both runnable three-file samples.')
