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
               const std::vector<OtusAlgo::Fibo::IntType>& a) {
    constexpr size_t CYCLES = 10;
    output << name << " : ";
    for (const value: a){
        auto start = std::chrono::system_clock::now();
        for (size_t j = 0; j < CYCLES; ++j){
            runner.Calculate(value);
        }
        auto end = std::chrono::system_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
        output << 1.*us/CYCLES << " us\t";
    }
    output << std::endl;
}

    
int main() {
    // for tests
    std::filesystem::path this_file = __FILE__;
    // elapsed time to save
    std::ofstream output(this_file.parent_path().string() + "/benchmark.txt");
    const std::vector<OtusAlgo::Fibo::IntType>& as{2, 15, 38};
    output << "Benchmark for input data: \n";
    for (size_t i = 1; i <= as.size(); ++i) {
        output << i << ". " << as[i-1] << "\n";
    }
    output << std::endl;

    {
    OtusAlgo::FiboRecursive fibo_recursive;
    OtusAlgo::Tester test(fibo_recursive, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Fibo Recursive", output, fibo_recursive, as);
    }

    {
    OtusAlgo::FiboIter fibo;
    OtusAlgo::Tester test(fibo, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Fibo Iter", output, fibo, as);
    }

    {
    OtusAlgo::FiboGolden fibo;
    OtusAlgo::Tester test(fibo, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Fibo Golden", output, fibo, as);
    }

    {
    OtusAlgo::FiboMatrix fibo;
    OtusAlgo::Tester test(fibo, this_file.parent_path().string() + "/tests");
    test.RunTests(5);
    // benchmark
    benchmark("Fibo Matrix", output, fibo, as);
    }



    return 0;
}
