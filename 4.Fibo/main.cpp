#include "Fibo.h"
#include <Tester.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>

namespace fs = std::filesystem;

void benchmark(const std::string& name,
               std::ofstream& output,
               const OtusAlgo::Fibo& runner,
               OtusAlgo::Fibo::IntType a) {
    constexpr size_t CYCLES = 10;
    auto start = std::chrono::system_clock::now();
    for (size_t i = 0; i < CYCLES; ++i){
        runner.Calculate(a);
    }
    auto end = std::chrono::system_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    output << name << " : " << 1.*us/CYCLES << " us" <<std::endl;

}

    
int main() {
    // for tests
    std::filesystem::path this_file = __FILE__;
    // elapsed time to save
    std::ofstream output(this_file.parent_path().string() + "/benchmark.txt");

    {
    OtusAlgo::FiboRecursive fibo_recursive;
    OtusAlgo::Tester test(fibo_recursive, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Fibo Recursive", output, fibo_recursive, 39);
    }

    {
    OtusAlgo::FiboIter fibo;
    OtusAlgo::Tester test(fibo, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Fibo Iter", output, fibo, 39);
    }

    {
    OtusAlgo::FiboGolden fibo;
    OtusAlgo::Tester test(fibo, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Fibo Golden", output, fibo, 39);
    }

    {
    OtusAlgo::FiboMatrix fibo;
    OtusAlgo::Tester test(fibo, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Fibo Matrix", output, fibo, 39);
    }



    return 0;
}
