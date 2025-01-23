set(BENCHMARK_TARGET Benchmarks)

include(FetchContent)
FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.0
)
FetchContent_MakeAvailable(benchmark)

add_executable(${BENCHMARK_TARGET}
  hello.cpp
)

target_link_libraries(${BENCHMARK_TARGET}
    benchmark::benchmark
)