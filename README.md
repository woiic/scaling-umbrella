# Scaling-Umbrella

A small C++ game/engine project for learning C++ and have some code for my job search. I made it using CMake and vcpkg for dependency management. This project Provides core engine pieces (Engine, Renderer, InputHandler, GameLogic) for 2D strategy games (tabletop games) and the example entry in `src/main.cpp`.

## What have I learned

To this day, I have learned a lot of C++, the diferences between Unreal Engine C++ and pure are clear, Unreal aids you a lot without you noticing and having to do everything by hand makes you notice it all.
I also have learn first hand the importance of planning ahead and having a log of my advances and achivements, the first one so I have at least a structure for the features I'm adding and not add stuff I don't need or let my code be hard to extend in the future when adding new features, and the second one to allways know what I have to do and what I have done, and to have a way to remind myself how much I have worked so far.

## Features
- Simple modular engine structure
- Uses vcpkg for third-party libraries
- CMake presets for reproducible builds
- Cross-platform build using Ninja or Visual Studio generators

## Prerequisites
- CMake (3.25+ recommended)
- Visual Studio 
- vcpkg (optional, referenced by `CMakePresets.json`)

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

## Project layout
- `CMakeLists.txt` — top-level CMake config
- `CMakePresets.json` — configure/build presets
- `src/` — source code and engine modules
- `assets/` — game assets
