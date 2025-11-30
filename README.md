# meengi-site

Personal website content for kosmoknot powered by the `meengi` static site generator.

## Run Configurations

- **Linux / macOS:** install a C++17-ready toolchain (`sudo apt install build-essential` or `xcode-select --install`). From the repo root run `make` (or `make site`) to build the site. This will compile the generator in `meengi/` and execute `./meengi/meengi` against the default `content/` tree.
- **Windows (WSL only):**
  1. Enable WSL2 and install Ubuntu/Debian from the Microsoft Store.
  2. Inside WSL run `sudo apt update && sudo apt install build-essential make gdb git`.
  3. Clone/open the repo within WSL (e.g. `/mnt/c/Users/<you>/kosmoknot-site-main`).
  4. Use `make` to build the generator and render the site content. `make meengi` is also available if you only need to compile the binary.
  5. With VS Code use the **Remote - WSL** extension and the `Make all` task plus `Debug Generator (WSL)` / `Debug Tests (WSL)` launch configs.

## Meengi generator

The `meengi/` directory is the standalone generator project. It now owns the former `code/` sources (`include/`, `src/`, and `bin/`) plus its own `Makefile`.

Typical commands:

- `make meengi` (or `make -C meengi`) – build the generator only.
- `make clean-meengi` – remove generator objects/binaries.
- `./meengi/meengi` – run the generator directly; without arguments it reads `content/directives/layout.md` and `content/directives/templates.md`, processes `content/*.md`, then writes HTML into `site/`.
- `make site` – orchestrates the two previous steps.

### CLI usage

`./meengi/meengi --help` documents the available switches. The most common flags are:

- `--content-root <dir>` – where markdown pages live (default `content/`).
- `--layout <file>` / `--templates <file>` – overrides for directive files; when omitted they default to `<content-root>/directives/layout.md` and `<content-root>/directives/templates.md`.
- `--output-dir <dir>` – directory for rendered HTML (defaults to the `site/` folder next to the chosen `content/` directory).
- `--warnings-file <file>` – destination for warnings (default `warnings.txt`).

These flags allow the same binary to render alternative content trees (for example the fixtures located under `meengi/tests/fixtures/`).

When you run the generator from inside the `meengi/` directory (`cd meengi && ./meengi`), the defaults fall back to the parent repo so it still targets `../content/` and writes into `../site/`.

For a deeper walkthrough (content structure, templates, shorthands), see `docs/MEENGI_USAGE.md`.

## Examples

`meengi/examples/` mirrors the required structure (`content/` plus `content/directives/`) with lightweight markdown (`index.md`, `about.md`) and directives (`layout.md`, `templates.md`). Use this folder to prototype layout changes or to demonstrate how the generator consumes markdown without touching the production content.

## Tests

Run `make -C meengi test` after editing the generator to execute the expanded unit suite under `meengi/tests/`. The fixtures in `meengi/tests/fixtures/` provide self-contained layouts, templates, and markdown that the tests (and developers) can reuse when experimenting with new features.
