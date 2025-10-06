# HybridTkApp — C++ Core + Tkinter UI

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
- **Python 3.8+ (including development headers and Tkinter)**
  - Windows: Official Python installer typically includes Tkinter and `python3.dll`
  - macOS: Recommended to use the installer from python.org or Homebrew (`brew install python`)
  - Ubuntu/Debian: `sudo apt-get install python3 python3-dev python3-tk`
- Internet connection (to fetch `pybind11` during initial CMake configuration. If already available locally, you can optionally use `find_package(pybind11 CONFIG REQUIRED)` instead)

## Build
```bash
# In the project root directory
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
# The executable will be located at: build/bin/hybrid_app[.exe]

```

> On Windows, if you encounter a runtime error about `python3.dll` not being found, add your Python installation directory (e.g., `C:\Users\<you>\AppData\Local\Programs\Python\Python312`) to your PATH, or copy the corresponding DLL to `build\bin`.

## Run
```bash
./build/bin/hybrid_app
```
If you encounter `No module named _tkinter`, please install the Tkinter component as described in the dependencies section above.
