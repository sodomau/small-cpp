from pathlib import Path
r=Path(__file__).resolve().parents[1]
checks={
 'ide/DebugController.cpp':['-exec-step','-exec-next','-exec-finish','-stack-list-variables','c_str()','-data-evaluate-expression'],
 'ide/CodeEditor.cpp':['breakpoints_','debugLine_'],
 'ide/MainWindow.cpp':['actionDebug','debugVariables','DebugController::stepInto'],
 'ide/CMakeLists.txt':['DebugController.h DebugController.cpp','VERSION 0.66'],
}
for f,tokens in checks.items():
 s=(r/f).read_text(encoding='utf-8')
 for t in tokens:
  assert t in s, f'{f}: missing {t}'
print('Debugger integration structure: OK')
