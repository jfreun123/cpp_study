set(TEST_TARGET SrcTests)
file(GLOB SOURCE_FILES *.cpp)

add_executable(${TEST_TARGET}
  ${SOURCE_FILES}
)
target_link_libraries(${TEST_TARGET}
  GTest::gtest_main
  cppstudysrc
)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})