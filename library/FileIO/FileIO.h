#pragma once

#include <filesystem>
#include <fstream>
#include <vector>
#include <type_traits>
#include <random>

namespace OtusAlgo {
template <typename Integer,
              std::enable_if_t<std::is_integral<Integer>::value, uint16_t> = 0
    >
void BinaryFileGenerator(const size_t n, Integer limit, std::filesystem::path fname) {
    auto test_in = fname.string() + ".in";
    std::ofstream input(test_in, std::ios::out | std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error("Cannot open file: " + test_in);
    }
    std::vector<Integer> statistics(limit, 0);
    std::random_device rd;
    std::mt19937::result_type seed = rd();
    std::mt19937 gen(seed);
    for (size_t i = 0; i < n; ++i) {
        Integer number = gen() % limit;
        input.write((char*)&number, sizeof(Integer));
        ++statistics[number];
    }
    
    auto test_out = fname.string() + ".out";
    std::ofstream output(test_out, std::ios::out | std::ios::binary);
    for (Integer i = 0; i < statistics.size(); ++i) {
        while(statistics[i] > 0) {
            output.write((char*)&i, sizeof(Integer));
            --statistics[i];
        }
    }
    
}

bool CompareBinaryFiles(std::filesystem::path lhs, std::filesystem::path rhs);

}
