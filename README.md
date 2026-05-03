# scaling-umbrella

A small C++ game/engine project using CMake and vcpkg for dependency management. Provides core engine pieces (Engine, Renderer, InputHandler, GameLogic) and the example entry in `src/main.cpp`.

## Features
- Simple modular engine structure
- Uses vcpkg for third-party libraries
- CMake presets for reproducible builds
- Cross-platform build using Ninja or Visual Studio generators

## Prerequisites
- CMake (3.25+ recommended)
- Ninja (recommended) or Visual Studio (matching generator)
- vcpkg (optional, referenced by `CMakePresets.json`)

## Quick build (recommended: Ninja + presets)
Configure (Debug):
```bash
cmake --preset default
```
Build:
```bash
cmake --build --preset default
```

If you prefer Visual Studio generators, run CMake with the appropriate `-G` option that matches your installed Visual Studio version (for example `-G "Visual Studio 17 2022"`).

## Run
After building, run the produced executable from the build directory, for example:
```powershell
.\build\Debug\SCALING_UMBRELLA.exe
```

## Getting started

1. Install vcpkg

- Clone vcpkg (choose an install location, example uses `D:/CGame/VCPKG`):
```powershell
git clone https://github.com/microsoft/vcpkg.git D:/CGame/VCPKG
cd D:/CGame/VCPKG
.\bootstrap-vcpkg.bat
```
- (Optional) Integrate vcpkg with MSBuild/CMake:
```powershell
.\vcpkg integrate install
```

2. Install packages with vcpkg

- Install libraries your project needs (example packages):
```powershell
D:/CGame/VCPKG/vcpkg install sdl2:x64-windows fmt:x64-windows
```
- The project uses the vcpkg toolchain file — ensure `CMakePresets.json` points to the correct `CMAKE_TOOLCHAIN_FILE` path.

3. Install MSYS2 + MinGW (for MinGW/GCC toolchain on Windows)

- Download and install MSYS2 from https://www.msys2.org and follow the on-site instructions.
- Update packages and install a MinGW-w64 toolchain from an MSYS2 shell:
```bash
pacman -Syu
# restart MSYS2 shell if required, then:
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```
- Add `C:\msys64\mingw64\bin` to your `PATH` (or use the MSYS2 MinGW64 shell) so `g++` is available.

4. Configure and build (example using presets)

```bash
cmake --preset default
cmake --build --preset default
```

Notes:
- `x64-windows` triplet is used above; if you use MinGW toolchain with vcpkg, you may need a corresponding triplet (e.g., `x64-mingw-dynamic`) and to set `CMAKE_TOOLCHAIN_FILE` appropriately.
- If by "mynsw" you meant a different compiler/package, tell me the exact name and I will add tailored install steps.

## Project layout
- `CMakeLists.txt` — top-level CMake config
- `CMakePresets.json` — configure/build presets
- `src/` — source code and engine modules
- `assets/` — game assets
