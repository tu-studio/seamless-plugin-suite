#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

TEST(Benchmark, Main){
    benchmark::RunSpecifiedBenchmarks();
    std::cout << "--------------------------------------------------------------" << std::endl;
}