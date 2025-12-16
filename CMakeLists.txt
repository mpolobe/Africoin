# Root-level CMakeLists.txt

# 1. Project Minimum Requirements
cmake_minimum_required(VERSION 3.10)
project(AfricoinCore LANGUAGES CXX VERSION 1.0.0)

# 2. C++ Standard & Compiler Flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Add common flags for security/optimization
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter")

# 3. Find External Dependencies (Required for a functional blockchain)
# These will rely on FindXXX.cmake scripts or vcpkg/conan in the future
# For now, we set a placeholder for the crypto libraries
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED)
# Later, we will include LevelDB, libsecp256k1, and Qt

# 4. Add the Source Code Subdirectories
# This directs CMake to find the CMakeLists.txt files inside each source folder
add_subdirectory(src) 
# We'll add src/test/ later when we implement the test runner

# 5. Define the Main Executable
# This assumes the main source files are in src/africoin-cli.cpp and src/africoin-qt.cpp
# This is a placeholder; actual files will be defined in src/CMakeLists.txt
# add_executable(africoin-cli src/main.cpp src/cli.cpp)
