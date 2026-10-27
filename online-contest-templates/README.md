# Generate VS Code snippets

`generate_snippets.py` reads every top-level `.cpp` template in a folder and
creates a VS Code snippets file. Each template becomes a snippet named
`template_<filename>`.

From this folder, run:

```bash
python3 generate_snippets.py
```

The script asks for:

1. **Template folder** — the folder containing the `.cpp` files. Press Enter
   to use the current folder.
2. **Output file name** — the snippets JSON filename. Press Enter to create
   `snippets.code-snippets` in the selected template folder.
