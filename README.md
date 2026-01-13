# cpp-website (Drogon)

This is a small C++ web server built with **Drogon**.

## Prerequisites

You need:

- **Conan 2** (`conan --version`)
- **CMake** (repo uses CMake 3.22+)
- **Ninja** (`ninja --version`)
- A C++ compiler (GCC/Clang)

On Ubuntu/Debian:

```bash
sudo apt update
sudo apt install -y cmake ninja-build g++
# Conan 2 install method varies; see https://docs.conan.io/2/
```

## Build

From the repo root:

```bash
# 1) Install dependencies with Conan and generate the CMake toolchain
mkdir -p build
conan install . \
  -of build \
  -s build_type=Release \
  -c tools.cmake.cmaketoolchain:generator=Ninja \
  --build=missing

# 2) Configure CMake using the Conan toolchain
cmake -S . -B build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_POLICY_DEFAULT_CMP0091=NEW

# 3) Build
cmake --build build
```

### Run

Run from the repo root so relative `./static/...` paths resolve:

```bash
./build/site
```

Then open:

- http://localhost:8080/
- http://localhost:8080/health

Stop with `Ctrl+C`.

## Presets (optional)

Conan generates CMake presets in `build/CMakePresets.json` and includes them via `CMakeUserPresets.json`.

- If your CMake is **3.23+**, you can configure/build using presets:

```bash
cmake --preset conan-release
cmake --build --preset conan-release
```

- If your CMake is **older than 3.23** (e.g. 3.22.x), use the manual commands in **Build** above.

## When something changes

- If you change dependencies in `conanfile.txt`, re-run:

```bash
conan install . -of build -s build_type=Release \
  -c tools.cmake.cmaketoolchain:generator=Ninja --build=missing
```

- If you want a clean rebuild:

```bash
rm -rf build
```

## Troubleshooting

- **See the exact failing compile/link command**:

```bash
cmake --build build -v
```

- **Where generated files are**:
  - Conan toolchain: `build/conan_toolchain.cmake`
  - Conan deps + CMake package configs: `build/*Config.cmake` etc.
  - CMake cache: `build/CMakeCache.txt`
  - Ninja files: `build/build.ninja`

- **Static files not found at runtime**: the server uses relative paths like `./static/pages/index.html`.
  - Run `./build/site` from the repo root, or change `src/main.cpp` to use an absolute path.
