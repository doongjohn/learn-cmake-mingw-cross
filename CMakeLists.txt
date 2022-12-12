cmake_minimum_required(VERSION 3.25)

# ----------------------------------------------
# - generate build files
# cmake -S . -B build -G Ninja
# ----------------------------------------------
# - build
# cmake --build build
# ----------------------------------------------
# - build and run executable
# cmake --build build -t run
# ----------------------------------------------

# set target operating to windows
set(CMAKE_SYSTEM_NAME Windows)

# set compiler to mingw
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER /usr/bin/x86_64-w64-mingw32-windres)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# my project
project(exe_from_linux
  LANGUAGES CXX
)

# get dependencies using CPM
include(cmake/CPM.cmake)
CPMAddPackage("gh:glfw/glfw#3.3.8")
CPMAddPackage("gh:fmtlib/fmt#9.1.0")
CPMAddPackage(
  GITHUB_REPOSITORY gabime/spdlog
  VERSION 1.x
  OPTIONS "SPDLOG_FMT_EXTERNAL ON"
)

# get all cpp source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME}
  ${SRC_FILES})

target_compile_features(${PROJECT_NAME}
  PRIVATE
    cxx_std_20)

target_link_options(${PROJECT_NAME}
  PRIVATE
    -static
    -static-libstdc++
    -static-libgcc)

target_link_libraries(${PROJECT_NAME}
  stdc++
  gdi32
  glfw
  spdlog::spdlog)

add_custom_target(run
  COMMAND ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
