"""Invalid lesson bundles must not silently pass validation."""
from pathlib import Path
import sys
import tempfile
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from tutorial_content import validate_pack

class LessonValidationTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.base = Path(self.temporary.name)
        self.lesson = self.base / '01_hello'
        self.lesson.mkdir()
        for name in ('example.cpp', 'starter.cpp', 'solution.cpp'):
            (self.lesson / name).write_text('void SmallMain() {}\n', encoding='utf-8')
        self.content = ('---\ntitle: Hello\ngoal: Say hello\npart: basics\npart-title: Basics\n'
                        'related-example: reference/console\n---\n'
                        '@code example.cpp\n@exercise starter.cpp\n@solution solution.cpp\n')
        self.write()
    def write(self):
        (self.lesson / 'ko.md').write_text(self.content, encoding='utf-8')
    def check(self):
        return validate_pack(self.base, ['ko', 'en'], 'ko', {'reference/console'})
    def test_missing_translation_uses_default(self):
        lessons, sources = self.check()
        self.assertEqual(len(lessons), 1)
        self.assertEqual(len(sources), 3)
    def test_missing_source_is_rejected(self):
        (self.lesson / 'example.cpp').unlink()
        with self.assertRaisesRegex(ValueError, 'Missing/empty source'):
            self.check()
    def test_solution_without_exercise_is_rejected(self):
        self.content = self.content.replace('@exercise starter.cpp\n', '')
        self.write()
        with self.assertRaisesRegex(ValueError, 'Orphan'):
            self.check()
    def test_parent_path_in_directive_is_rejected(self):
        self.content = self.content.replace('@code example.cpp', '@code ../example.cpp')
        self.write()
        with self.assertRaisesRegex(ValueError, 'Invalid code directive'):
            self.check()
    def test_unknown_related_example_is_rejected(self):
        self.content = self.content.replace('reference/console', 'reference/missing')
        self.write()
        with self.assertRaisesRegex(ValueError, 'Unknown related example'):
            self.check()
    def test_duplicate_lesson_number_is_rejected(self):
        (self.base / '01_other').mkdir()
        with self.assertRaisesRegex(ValueError, 'Duplicate lesson'):
            self.check()
if __name__ == '__main__':
    unittest.main()
