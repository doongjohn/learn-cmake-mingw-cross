cmake_minimum_required(VERSION 3.24)

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
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# get dependencies using CPM
include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#7.1.3")
CPMAddPackage("gh:gabime/spdlog#v1.x")
CPMAddPackage("gh:glfw/glfw#3.3.8")

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# my project
project(exe_from_linux
  LANGUAGES CXX
)

# get all cpp source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(
  ${PROJECT_NAME}
  ${SRC_FILES})

target_compile_features(
  ${PROJECT_NAME}
  PRIVATE cxx_std_20)

target_link_options(
  ${PROJECT_NAME}
  PRIVATE
  -static
  -static-libstdc++
  -static-libgcc)

target_link_libraries(
  ${PROJECT_NAME}
  stdc++
  gdi32
  fmt::fmt
  spdlog::spdlog
  glfw)

add_custom_target(run
  COMMAND ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
