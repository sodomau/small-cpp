"""Exercise the real pause object with stdin kept open until Enter is supplied."""
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time

compiler, pause_object = sys.argv[1:]
root = Path(__file__).resolve().parents[1]
for controller in ('BuildController.cpp', 'DebugController.cpp'):
    text = (root / 'ide' / controller).read_text(encoding='utf-8')
    assert 'idePausePath_' in text and '--whole-archive' not in text

with tempfile.TemporaryDirectory() as directory:
    directory = Path(directory)
    source = directory / 'main.cpp'
    source.write_text('int main() { return 0; }\n', encoding='utf-8')
    environment = dict(os.environ)
    environment.pop('SMALL_TEST_NO_CONSOLE_PAUSE', None)
    environment['PATH'] = str(Path(compiler).parent) + os.pathsep + environment.get('PATH', '')
    for include_pause in (False, True):
        binary = directory / ('paused.exe' if include_pause else 'plain.exe')
        args = [compiler, str(source)]
        if include_pause:
            args += [pause_object]
        args += ['-o', str(binary)]
        subprocess.run(args, check=True, env=environment)
        process = subprocess.Popen([str(binary)], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE, env=environment)
        try:
            if include_pause and os.name == 'nt':
                try:
                    process.wait(timeout=1)
                except subprocess.TimeoutExpired:
                    pass
                else:
                    raise AssertionError('IDE program exited without waiting for Enter')
            else:
                assert process.wait(timeout=5) == 0
            output, errors = process.communicate(input=b'\n', timeout=5)
            assert process.returncode == 0 and not errors
            assert (b'Press Enter to exit...' in output) == (include_pause and os.name == 'nt')
        finally:
            if process.poll() is None:
                process.kill()
                process.communicate()
    environment['SMALL_TEST_NO_CONSOLE_PAUSE'] = '1'
    result = subprocess.run([str(directory / 'paused.exe')], input=b'', capture_output=True,
                            env=environment, timeout=5)
    assert result.returncode == 0 and result.stdout == b'' and result.stderr == b''
    # Windows can retain the executable mapping briefly after process exit.
    for binary in directory.glob('*.exe'):
        for attempt in range(30):
            try:
                binary.unlink()
                break
            except PermissionError:
                if attempt == 29:
                    raise
                time.sleep(0.1)
print('IDE object waits for Enter; standalone and test-mode programs exit immediately.')
