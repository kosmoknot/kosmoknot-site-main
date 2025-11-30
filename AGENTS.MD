Use the C++ generator to write code.
Avoid javascript whenever possible, use html css and create a static website
Create templates and use md files

How to use the C++ generator (code/src):
1. Run `make && ./meengi` from the repo root; the binary reads `content/directives/layout.md` to build the site map, then pulls templates from `content/directives/templates.md`, page content from `content/*.md`, and finally writes rendered HTML to `site/*.html`.
2. Keep the layout tree valid: define each page under a `## Parent` heading with child lines prefixed by `#`, and never list the same child under multiple parents.
3. When adding markup inside markdown pages, rely on the built-in shorthand parser (`**bold**`, `*italic*`, `` `code` ``, `/nl`, `/hline`, etc.) instead of dropping to raw HTML or JavaScript.
4. To create reusable structures, add templates to `templates.md`; call them via `$TemplateName(args)` inside content and let the parser expand them, avoiding JS-based includes.
5. Only edit files under `content/` and the template directives; the generator maintains `site/` output, so never hand-edit the generated HTML.
