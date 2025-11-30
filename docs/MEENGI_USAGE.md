# Meengi Usage Guide

This generator reads three inputs:

- **Layout**: the sitemap tree in `content/directives/layout.md` (one `##Parent` per section, children prefixed with `#`).
- **Templates**: reusable HTML/markup snippets in `content/directives/templates.md` (define with `$Name(args)` blocks).
- **Pages**: markdown-like content files in `content/*.md` that use shorthand (e.g., `**bold**`, `/nl`) and call templates (`$Header()$`).

It produces HTML into the output directory (default: `site/`).

## CLI

```
./meengi/meengi [--content-root DIR] [--layout FILE] [--templates FILE] \
                [--output-dir DIR] [--warnings-file FILE]
```

Defaults resolve relative to the current working directory:
- If `--content-root` is omitted, Meengi looks for `./content` or `../content` (useful when running from inside `meengi/`).
- `--layout` and `--templates` default to `<content-root>/directives/layout.md` and `<content-root>/directives/templates.md`.
- `--output-dir` defaults to a sibling `site/` folder next to the chosen content directory.
- `--warnings-file` defaults to `warnings.txt` next to the chosen content directory.

Examples:
- Render the main site from repo root: `./meengi/meengi`
- Render from inside `meengi/`: `cd meengi && ./meengi` (targets `../content` → `../site`).
- Render a custom tree: `./meengi/meengi --content-root meengi/examples/content --output-dir meengi/examples/site`

## Structure expectations

- Every page listed under a parent in `layout.md` must have a matching `content/<name>.md` file.
- Page names are trimmed; stray whitespace/CR characters in `layout.md` are ignored.
- Template arguments expand via `$$arg$$` placeholders inside `templates.md`; missing arguments render as empty strings.

## Shorthand rendering

`ShortHandParser` converts a small subset of markdown-like syntax:
- `**bold**` → `<b>bold</b>`
- `*italic*` → `<i>italic</i>`
- `# heading` → `<h1>heading</h1>`
- `` `code` `` → `<pre>code</pre>`
- `/nl` → `<br><br>`
- `/hline` → `<div class=" hrcls"><hr></ div>`

## Cleaning and warnings

- `ClearPreviousFiles()` removes only `.html` files from the output directory and truncates the warnings file.
- Warnings (e.g., duplicate layout entries, unknown parents) are appended to the configured warnings file.

## Testing

From repo root: `make -C meengi test`

Tests use fixtures in `meengi/tests/fixtures/basic` so they don’t touch production content.
