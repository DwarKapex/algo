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

template<typename Integer = char>
std::vector<Integer> ReadBinaryFile(const std::filesystem::path& input_fname) {
    std::ifstream input(input_fname.string(), std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error("Cannot open file: " + input_fname.string());
    }
    input.seekg(0, std::ios::end);
    auto input_size = input.tellg();
    std::vector<Integer> buf(input_size);
    input.seekg(0, std::ios::beg);
    input.read(buf.data(), input_size);
    input.close();
    return buf;
}

template<typename Integer = char>
bool WriteBinaryFile(const std::filesystem::path& output_fname, const std::vector<Integer>& data){
    std::ofstream output(output_fname.string(), std::ios::binary);
    if (!output.is_open()) {
        throw std::runtime_error("Cannot open file: " + output_fname.string());
    }
   
    for (const auto& b: data) {
        output.write((char*)&b, sizeof(Integer));
    }
    output.close();
    return true;
}
}
