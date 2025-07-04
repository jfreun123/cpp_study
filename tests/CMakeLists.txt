set(TEST_TARGET SrcTests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${TEST_TARGET}
  lisp_parser_test.cpp
  primes_test.cpp
  set_intersection_test.cpp
  spinlock_test.cpp
  sudoku_test.cpp
  threadsafesharedpointer_test.cpp
)

target_link_libraries(${TEST_TARGET}
  GTest::gtest_main
  cppstudysrc
)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})