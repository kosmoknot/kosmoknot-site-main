# meengi-site

Personal website generator for kosmoknot.

## Run Configurations

- **Linux / macOS:** install a C++17-capable toolchain (`sudo apt install build-essential` or `xcode-select --install`), then run `make && ./meengi` from the repo root. `make test` runs the unit suite and `make clean` resets build artifacts.

- **Windows (WSL only):**
  1. Enable WSL2 and install Ubuntu (or Debian) from the Microsoft Store.
  2. Inside the WSL terminal run `sudo apt update && sudo apt install build-essential make gdb git`.
  3. Clone or open the repo within WSL (e.g., `/mnt/c/Users/<you>/kosmoknot-site-main`) and run `make && ./meengi`.
  4. Use `make test` for the unit suite and `make clean` to reset build outputs.
  5. When using VS Code, open the folder via the **Remote - WSL** extension and use the provided `Make all` task plus the `Debug Generator (WSL)` / `Debug Tests (WSL)` launch configurations.

## Tests

`make test` builds and runs the lightweight unit suite in `tests/`; use it after editing the generator to ensure regressions are caught early.
