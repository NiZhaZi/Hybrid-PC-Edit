# HybridTkApp — C++ Core + Dear Imgui UI

- Rebuild from tkinter to imgui

## Directory Structure
```
hybrid_tk_app/
├─ CMakeLists.txt
└─ src/
   ├─ core.hpp          
   ├─ core.cpp          
   └─ main_embedded.cpp
```

## Dependencies
- CMake ≥ 3.20
- C++17 Compiler (MSVC 2019+/GCC 9+/Clang 10+)

## Build
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make

```

## Run
```bash
./bin/hybrid_app
```
