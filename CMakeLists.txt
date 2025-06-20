cmake_minimum_required(VERSION 3.14)
project(CPPStudy VERSION 1.0)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(tests)
# add_subdirectory(benchmarks) #TODO(self):  fix for macbook
