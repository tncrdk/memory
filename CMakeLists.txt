# memory_benchmark/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(memory_benchmark VERSION 1.0.0 LANGUAGES CXX)
# include(CMakePrintHelpers)

# Create the shared library
add_library(memory_benchmark SHARED
    memory_benchmark.cpp
)

# Specify include directories for the library itself
target_include_directories(memory_benchmark PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
# cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)

# Install rules for the library
install(TARGETS memory_benchmark
    EXPORT memory_benchmark_targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin # For Windows DLLs
)

# Install headers
install(FILES
    memory_benchmark.h
    DESTINATION include
)

# Generate and install the package configuration file
# This is crucial for find_package to work correctly
install(EXPORT memory_benchmark_targets
    FILE memory_benchmarkConfig.cmake
    NAMESPACE memory_benchmark::
    DESTINATION lib/cmake/memory_benchmark
)

# Create a package configuration file for find_package(memory_benchmark)
# This content will be written to memory_benchmarkConfigVersion.cmake and lib_aConfig.cmake during install
# For simple cases, memory_benchmarkConfig.cmake might just contain include(lib_aTargets.cmake)
# For more complex cases, you might generate it with configure_file
# Example simplified content for find_package(memory_benchmark CONFIG)
set(memory_benchmark_VERSION ${PROJECT_VERSION})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/memory_benchmarkConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/memory_benchmarkConfig.cmake @ONLY
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/memory_benchmarkConfig.cmake
    DESTINATION lib/cmake/memory_benchmark
)
