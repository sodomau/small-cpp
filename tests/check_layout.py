"""Structural regression checks; these do not replace a real Qt build."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
header = (root / 'runtime/small.h').read_text()
controller = (root / 'ide/BuildController.cpp').read_text()
window = (root / 'ide/MainWindow.cpp').read_text()
cmake = (root / 'ide/CMakeLists.txt').read_text()
checks = {
    'public header contains no Qt includes': not re.search(r'#include\s*[<"]Q', header),
    'public API lives in Small namespace': 'namespace Small' in header,
    'beginner using is macro guarded': '#ifdef SMALL_BEGINNER_MODE' in header and 'using namespace Small;' in header,
    'learner build enables beginner mode': '-DSMALL_BEGINNER_MODE' in controller,
    'SmallMain is the learner entry point': 'void SmallMain();' in header and 'SmallMain();' in (root / 'runtime/small_main.cpp').read_text(),
    'Window does not inherit QWidget in public API': 'public QWidget' not in header,
    'fixed real main exists': 'int main(' in (root / 'runtime/small_main.cpp').read_text(),
    'runtime prebuilt by CMake': 'add_library(small_runtime STATIC' in cmake,
    'IDE depends on the packaged runtime': 'add_dependencies(SmallCppIDE small_sdk)' in cmake,
    'no blocking process waits in IDE': not any('waitFor' in p.read_text() for p in (root/'ide').glob('*.cpp')),
    'no qmake subprocess per Run': 'qmake' not in controller,
    'learner compilation has no Qt header paths': 'qtHeaders' not in controller,
    'no runtime compilation in runner': 'small_runtime.cpp' not in controller and 'small_main.cpp' not in controller,
    'close event uses save confirmation': 'void MainWindow::closeEvent' in window and 'maybeSaveAll()' in window,
    'all three save choices exist': 'QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel' in window,
    'save is atomic': 'QSaveFile file(destination)' in window and '!file.commit()' in window,
    'Ctrl+S assigned': '"actionSave", QKeySequence::Save,' in window,
    'default save name is provided': 'dialog.selectFile(document->displayName())' in window,
    'sound is still PCM, not OS beep': 'QAudioSink' in (root/'runtime/small_sound.cpp').read_text()
        and 'QApplication::beep' not in (root/'runtime/small_sound.cpp').read_text(),
    'tabs use widget identity rather than parallel index state':
        'qobject_cast<EditorDocument*>(tabs_->widget(index))' in window and
        'tabs_->indexOf(document)' in window,
    'Run tracks originating tab using a guarded pointer':
        'QPointer<EditorDocument> runDocument_' in (root/'ide/MainWindow.h').read_text(),
    'save-as protects other open documents': 'findOpenDocument(destination, document)' in window,
    'std::string inbound constructor exists': 'String(const std::string& text)' in header,
    'no generated machine-specific CMake cache included': not list(root.rglob('CMakeCache.txt')),
}
for name, ok in checks.items():
    print(('PASS ' if ok else 'FAIL ') + name)
if not all(checks.values()):
    raise SystemExit(1)
print(f'{len(checks)} structural checks passed')
