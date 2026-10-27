#!/usr/bin/env python3
"""Generate a VS Code snippets file from a folder of C++ templates."""

import json
from pathlib import Path
import sys


def prompt(message: str, default: str) -> str:
    value = input(f"{message} [{default}]: ").strip()
    return value or default


def main() -> None:
    folder_text = prompt("Template folder", ".")
    template_dir = Path(folder_text).expanduser().resolve()
    if not template_dir.is_dir():
        print(f"Error: not a directory: {template_dir}", file=sys.stderr)
        raise SystemExit(1)

    output_name = prompt("Output file name", "snippets.code-snippets")
    output_path = Path(output_name).expanduser()
    if not output_path.is_absolute():
        output_path = template_dir / output_path

    source_files = sorted(
        path for path in template_dir.glob("*.cpp") if path.is_file()
    )
    if not source_files:
        print(f"Error: no .cpp files found in {template_dir}", file=sys.stderr)
        raise SystemExit(1)

    snippets = {}
    for source_path in source_files:
        stem = source_path.stem
        snippet_name = f"template_{stem}"
        snippets[snippet_name] = {
            "prefix": snippet_name,
            "body": source_path.read_text(encoding="utf-8").splitlines(),
        }

    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(
        json.dumps(snippets, indent=4, ensure_ascii=False) + "\n",
        encoding="utf-8",
    )
    print(f"Wrote {len(snippets)} snippets to {output_path}")


if __name__ == "__main__":
    main()
