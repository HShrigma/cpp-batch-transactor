cmake_minimum_required(VERSION 3.20)
project(cpp_batch_transactor)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
# Find libpqxx
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

# Include directories
include_directories(
    ${LIBPQXX_INCLUDE_DIRS}
    include
)

# Source files
file(GLOB SOURCES "src/*.cpp" "src/transaction/*.h" "src/transaction/*.cpp")

# Executable
add_executable(transactor ${SOURCES})

# Link Libs
target_link_libraries(transactor ${LIBPQXX_LIBRARIES})