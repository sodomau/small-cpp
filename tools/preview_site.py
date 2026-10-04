"""Build a local project-page preview using the repository's existing artwork."""
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import argparse
from build_site import build

ROOT = Path(__file__).resolve().parent.parent


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=8765)
    parser.add_argument('--build-only', action='store_true')
    args = parser.parse_args()
    output = build()
    print(f'Preview files: {output}', flush=True)
    if args.build_only:
        return

    class PreviewHandler(SimpleHTTPRequestHandler):
        def __init__(self, *values, **kwargs):
            super().__init__(*values, directory=str(output), **kwargs)

    print(f'open http://127.0.0.1:{args.port} (Ctrl+C to stop)', flush=True)
    with ThreadingHTTPServer(('127.0.0.1', args.port), PreviewHandler) as server:
        server.serve_forever()


if __name__ == '__main__':
    main()
