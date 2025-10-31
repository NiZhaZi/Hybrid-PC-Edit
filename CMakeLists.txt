cmake_minimum_required(VERSION 3.20)
project(HybridTkApp)  # project name kept

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ---- GLFW ----
FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(gl3w
  GIT_REPOSITORY https://github.com/skaslev/gl3w.git
  GIT_TAG master
)
FetchContent_MakeAvailable(gl3w)

# ---- Dear ImGui ----
FetchContent_Declare(imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.92.4-docking
)
FetchContent_MakeAvailable(imgui)

# ImGui sources + backends (OpenGL2 to avoid custom GL loader)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
add_library(imgui STATIC
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp
  ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)
target_include_directories(imgui PUBLIC
  ${IMGUI_DIR}
  ${IMGUI_DIR}/backends
  ${IMGUI_DIR}/misc/cpp
)

include_directories(${gl3w_BINARY_DIR}/include)
include_directories(${imgui_SOURCE_DIR}/examples/libs/glfw/include)

# OpenGL
find_package(OpenGL REQUIRED)

# ---- App ----
add_executable(hybrid_app
  src/main_embedded.cpp
  src/core.cpp
)

# Hide the console window on Windows by using the WINDOWS subsystem
if (WIN32)
  set_target_properties(hybrid_app PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

target_include_directories(hybrid_app PRIVATE src)
target_link_libraries(hybrid_app PRIVATE imgui glfw OpenGL::GL)

# Runtime dir layout
set_target_properties(hybrid_app PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Install rule
install(TARGETS hybrid_app RUNTIME DESTINATION .)
