cmake_minimum_required(VERSION 3.25)

# ----------------------------------------------
# - generate build files
# cmake -S . -B build -G Ninja
# ----------------------------------------------
# - build
# cmake --build build
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
CPMAddPackage("gh:fmtlib/fmt#9.1.0")
CPMAddPackage(
  GITHUB_REPOSITORY gabime/spdlog
  VERSION 1.x
  OPTIONS "SPDLOG_FMT_EXTERNAL ON")
CPMAddPackage(
  NAME nlohmann_json
  VERSION 3.11.2
  # the git repo is incredibly large, so we download the archived include directory
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/include.zip
  URL_HASH SHA256=e5c7a9f49a16814be27e4ed0ee900ecd0092bfb7dbfca65b5a421b774dccaaed)
if (nlohmann_json_ADDED)
  add_library(nlohmann_json INTERFACE IMPORTED)
  target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR}/include)
endif()

# get all cpp source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_features(${PROJECT_NAME}
  PRIVATE cxx_std_20)

target_link_options(${PROJECT_NAME}
  PRIVATE -static
  PRIVATE -static-libgcc
  PRIVATE -static-libstdc++)

target_link_libraries(${PROJECT_NAME}
  gdi32
  spdlog::spdlog
  nlohmann_json)
