"""Build a local project-page preview using the repository's existing artwork."""
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import argparse
import shutil

ROOT = Path(__file__).resolve().parent.parent


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=8765)
    parser.add_argument('--build-only', action='store_true')
    args = parser.parse_args()
    output = ROOT / 'build' / 'project-page'
    output.mkdir(parents=True, exist_ok=True)
    for name in ('index.html', 'style.css', 'app.js'):
        shutil.copy2(ROOT / 'site' / name, output / name)
    assets = output / 'assets'
    assets.mkdir(exist_ok=True)
    for source in (ROOT / 'ide/assets/smallcpp_128.png', ROOT / 'docs/images/ide-dark.png', ROOT / 'docs/images/ide-light.png'):
        shutil.copy2(source, assets / source.name)
    print(f'Preview files: {output}', flush=True)
    if args.build_only:
        return

    class PreviewHandler(SimpleHTTPRequestHandler):
        def __init__(self, *values, **kwargs):
            super().__init__(*values, directory=str(ROOT), **kwargs)

        def do_GET(self):
            if self.path == '/' or self.path.startswith('/assets/') or self.path in ('/style.css', '/app.js'):
                self.path = '/build/project-page' + ('/index.html' if self.path == '/' else self.path)
            super().do_GET()

    print(f'Open http://127.0.0.1:{args.port} (Ctrl+C to stop)', flush=True)
    with ThreadingHTTPServer(('127.0.0.1', args.port), PreviewHandler) as server:
        server.serve_forever()


if __name__ == '__main__':
    main()
