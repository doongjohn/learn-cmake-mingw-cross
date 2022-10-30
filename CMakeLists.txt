cmake_minimum_required(VERSION 3.24)

project(Test
  LANGUAGES CXX
)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_GENERATOR_PLATFORM win32)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-gcc)

# get all cpp source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(
  test
  ${SRC_FILES})
target_compile_features(
  test
  PRIVATE cxx_std_20)
target_link_options(
  test
  PRIVATE
  -static
  -static-libstdc++
  -static-libgcc)
target_link_libraries(
  test
  stdc++
  gdi32)
target_include_directories(
  test
  PRIVATE /usr/x86_64-w64-mingw32/include)
