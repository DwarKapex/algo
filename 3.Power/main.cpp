#include "Power.h"
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
               const OtusAlgo::Power& runner,
               const std::vector<OtusAlgo::Power::FloatType>& a,
               const std::vector<OtusAlgo::Power::IntType>& b) {
    constexpr size_t CYCLES = 10;
    output << name << " : ";
    for (int i = 0; i < a.size(); ++i) {
        auto start = std::chrono::system_clock::now();
        for (size_t j = 0; j < CYCLES; ++j){
            runner.Calculate(a[i],b[i]);
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
    const std::vector<OtusAlgo::Power::FloatType>& as{2, 1.0001, 1.000000001};
    const std::vector<OtusAlgo::Power::IntType>& bs{10, 1000, 1000000000};
    output << "Benchmark for input data: \n";
    for (size_t i = 1; i <= as.size(); ++i) {
        output << i << ". " << std::setprecision(20) << as[i-1] << "^" << bs[i-1] << "\n";
    }
    output << std::endl;

    {
    OtusAlgo::PowerMultiplication p;
    OtusAlgo::Tester test(p, this_file.parent_path().string() + "/tests");
    test.RunTests(6);
    // benchmark
    benchmark("Power Multiplication", output, p, as, bs);
    }

    {
    OtusAlgo::Power2 p;
    OtusAlgo::Tester test(p, this_file.parent_path().string() + "/tests");
    test.RunTests(7);
    // benchmark
    benchmark("Power2", output, p, as, bs);
    }
    
    {
    OtusAlgo::PowerBinary p;
    OtusAlgo::Tester test(p, this_file.parent_path().string() + "/tests");
    test.RunTests(7);
    // benchmark
    benchmark("Power Binary", output, p, as, bs);
    }


    return 0;
}
