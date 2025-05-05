cmake_minimum_required(VERSION 3.20)
project(cpp_batch_transactor)

set(CMAKE_CXX_STANDARD 20)

# Find pkg-config
find_package(PkgConfig REQUIRED)

# Find libpqxx using pkg-config
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

# Include directories
include_directories(
    ${LIBPQXX_INCLUDE_DIRS}  # Include directories from libpqxx
    include  # Your local header files
)

# Source files
file(GLOB SOURCES 
    "src/*.cpp" 
    "src/transaction/*.cpp" 
    "src/io/*.cpp" 
    "src/transaction/helpers/*.cpp" 
    "src/transaction/*.h" 
    "src/io/*.h" 
    "src/transaction/helpers/*.h"
    "include/*.hpp"
)

# Executable
add_executable(transactor ${SOURCES})

# Link libraries (libpqxx)
target_link_libraries(transactor ${LIBPQXX_LIBRARIES})

# Ensure C++ standard is properly set for your compiler
target_compile_features(transactor PRIVATE cxx_std_20)

# For debugging
message(STATUS "libpqxx include dirs: ${LIBPQXX_INCLUDE_DIRS}")
message(STATUS "libpqxx libraries: ${LIBPQXX_LIBRARIES}")
