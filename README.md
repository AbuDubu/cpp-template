# cpp-template

A small CMake template for C and C++ projects: a static library, an app, GoogleTest tests,
Google Benchmark benchmarks, compiler warnings, sanitizers, clang-tidy and GitHub Actions CI.

## Start a new project from it

1. On GitHub, click **Use this template** → **Create a new repository**.
2. In `CMakeLists.txt`, change the name in `project(cpp_template ...)`.
3. Replace the sample code in `src/`, `app/`, `tests/` and `bench/` with your own and update
   the source lists in `CMakeLists.txt`.

## Requirements

CMake 3.25+, Ninja, and GCC or Clang with C17 and C++20 support. GoogleTest and Google
Benchmark are downloaded automatically during configure. On Fedora, sanitizer builds with GCC
also need `sudo dnf install libasan libubsan libtsan`.

## Build, test, run

```sh
cmake --preset dev              # configure into build/dev
cmake --build --preset dev      # compile
ctest --preset dev              # run the tests
./build/dev/app
```

Or configure, build and test in one command: `cmake --workflow --preset ci`.

## Presets

| Preset    | What it is                                         | Use it for                       |
|-----------|----------------------------------------------------|----------------------------------|
| `dev`     | Debug (`-g`)                                       | Everyday work, gdb               |
| `release` | Release (`-O3 -DNDEBUG`)                           | Checking optimized behavior      |
| `asan`    | Debug + AddressSanitizer + UBSan                   | Memory bugs, undefined behavior  |
| `tsan`    | Debug + ThreadSanitizer                            | Data races                       |
| `bench`   | Release + benchmarks, no tests                     | `./build/bench/stats_bench`      |
| `tidy`    | Debug + clang-tidy on every file during the build  | Static analysis                  |
| `ci`      | Debug, warnings are errors                         | What GitHub Actions runs         |

Workflow presets (`cmake --workflow --preset <name>`): `ci`, `asan`, `tsan`.

To use Clang, set the compiler before the first configure of a preset:
`CC=clang CXX=clang++ cmake --fresh --preset dev`.

## Layout

```
CMakeLists.txt        targets: core (library), app, unit_tests, stats_bench
CMakePresets.json     the presets above
src/                  library code; headers live next to sources
app/main.cpp          the program
tests/                GoogleTest tests
bench/                Google Benchmark benchmarks
.clang-format         code style: clang-format -i <files>
.clang-tidy           static analysis checks used by the tidy preset
.github/workflows/    CI: GCC and Clang × ci, asan, tsan
```

## Notes

- Warnings (`-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2`) apply only to this
  project's targets, through the `project_warnings` interface library, not to dependencies.
- C files are compiled as strict C17 with `_GNU_SOURCE`, so POSIX and Linux APIs are available.
- Put personal presets in `CMakeUserPresets.json`. It is git-ignored.
