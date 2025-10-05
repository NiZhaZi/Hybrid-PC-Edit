cmake_minimum_required(VERSION 3.20)
project(HybridTkApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch pybind11 (header-only). You can comment this block if pybind11 is installed system-wide.
include(FetchContent)
FetchContent_Declare(pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.12.0
)
FetchContent_MakeAvailable(pybind11)

# Python development headers & libs (for the embedded interpreter)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

add_executable(hybrid_app
    src/main_embedded.cpp
    src/core.cpp
)

target_include_directories(hybrid_app PRIVATE src)
target_link_libraries(hybrid_app PRIVATE pybind11::embed Python3::Python)

# Nice output dir layout
set_target_properties(hybrid_app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Install rule
install(TARGETS hybrid_app RUNTIME DESTINATION .)
