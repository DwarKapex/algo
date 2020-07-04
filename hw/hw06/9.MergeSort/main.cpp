#include "MergeSort.h"
#include <FileIO.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <map>

namespace fs = std::filesystem;
std::filesystem::path this_file = __FILE__;

using IntType = uint16_t;

void generate_test(const size_t n, fs::path fname) {
    OtusAlgo::BinaryFileGenerator(n, std::numeric_limits<IntType>::max(), fname);
}

void benchmark(std::map<std::string, std::vector<size_t>>& result, const size_t size, const std::filesystem::path& fin_path, const std::filesystem::path& fout_path) {
    // copy test file into temp one
    std::vector<size_t> chunks{32, 128, 512, 1024};
    fs::path temp_file("/tmp/result.out");
    fs::copy_file(fin_path, temp_file, fs::copy_options::overwrite_existing);
    
    
    for (const auto chunk: chunks) {
        OtusAlgo::MergeSortChunk<IntType> temp_sort;
        OtusAlgo::MergeSort<IntType> s(temp_file, temp_sort, chunk);
        auto start = std::chrono::system_clock::now();
        s.sort();
        auto end = std::chrono::system_clock::now();
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
        assert(OtusAlgo::CompareBinaryFiles(temp_file, fout_path));
        std::string key = "ClassicMergeSort_"+std::to_string(chunk);
        result[key].push_back(sec);
        std::cout << "ClassicMergeSort with chunk size = " << chunk << " done\n";
    }
    
    
    for (const auto chunk: chunks) {
        OtusAlgo::QuickSortChunk<IntType> temp_sort;
        OtusAlgo::MergeSort<IntType> s(temp_file, temp_sort, chunk);
        auto start = std::chrono::system_clock::now();
        s.sort();
        auto end = std::chrono::system_clock::now();
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
        assert(OtusAlgo::CompareBinaryFiles(temp_file, fout_path));
        std::string key = "Merge+QuickSort_"+std::to_string(chunk);
        result[key].push_back(sec);
        std::cout << "MergeSort + QuickSort with chunk size = " << chunk << " done\n";
    }
    
    {
    // counting sort
    std::vector<IntType> data(size, 0);
    std::ifstream fin(fin_path.string(), std::ios::in | std::ios::binary);
    fin.read(reinterpret_cast<char*>(data.data()), size*sizeof(IntType));
    fin.close();
    OtusAlgo::CountingSort<IntType> counting_sort;
    auto start = std::chrono::system_clock::now();
    counting_sort.sort(data);
    auto end = std::chrono::system_clock::now();
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
    std::ofstream fout(temp_file.string(), std::ios::out | std::ios::binary);
    fout.write(reinterpret_cast<char*>(data.data()), size*sizeof(IntType));
    fout.close();
    assert(OtusAlgo::CompareBinaryFiles(temp_file, fout_path));
    std::string key = "CountingSort";
    result[key].push_back(sec);
    std::cout << "CountingSort done\n";
    }
    
    {
    // redix sort
    std::vector<IntType> data(size, 0);
    std::ifstream fin(fin_path.string(), std::ios::in | std::ios::binary);
    fin.read(reinterpret_cast<char*>(data.data()), size*sizeof(IntType));
    fin.close();
    OtusAlgo::RedixSort<IntType> redix_sort;
    auto start = std::chrono::system_clock::now();
    redix_sort.sort(data);
    auto end = std::chrono::system_clock::now();
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
    std::ofstream fout(temp_file.string(), std::ios::out | std::ios::binary);
    fout.write(reinterpret_cast<char*>(data.data()), size*sizeof(IntType));
    fout.close();
    assert(OtusAlgo::CompareBinaryFiles(temp_file, fout_path));
    std::string key = "RedixSort";
    result[key].push_back(sec);
    std::cout << "RedixSort done\n";
    }
    
    {
    // bucket sort
    std::vector<IntType> data(size, 0);
    std::ifstream fin(fin_path.string(), std::ios::in | std::ios::binary);
    fin.read(reinterpret_cast<char*>(data.data()), size*sizeof(IntType));
    fin.close();
    OtusAlgo::BucketSort<IntType> sort;
    auto start = std::chrono::system_clock::now();
    sort.sort(data);
    auto end = std::chrono::system_clock::now();
    auto sec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::ofstream fout(temp_file.string(), std::ios::out | std::ios::binary);
    fout.write(reinterpret_cast<char*>(data.data()), size*sizeof(IntType));
    fout.close();
    assert(OtusAlgo::CompareBinaryFiles(temp_file, fout_path));
    std::string key = "BucketSort";
    result[key].push_back(sec);
    std::cout << "BucketSort done\n";
    }

}

    
int main() {
    std::ofstream benchmark_out(this_file.parent_path().string() + "/benchmark.txt");
    
    std::map<std::string, std::vector<size_t>> result;
    std::vector<size_t> sizes{1000000, 10000000, 100000000, 1000000000};
    for (size_t n = 0; n < sizes.size(); ++n) {
        generate_test(sizes[n], this_file.parent_path() / "test"/ ("test." + std::to_string(n)));
    }
    
    for (size_t n = 0; n < sizes.size(); ++n) {
        benchmark(result, sizes[n], this_file.parent_path() / "test"/ ("test." + std::to_string(n) + ".in"),
                  this_file.parent_path() / "test"/ ("test." + std::to_string(n) + ".out"));
    }
        
    benchmark_out << std::setw(25) << "Algorithm";
    for (const auto s: sizes) {
        benchmark_out << std::setw(20) << s;
    }
    benchmark_out << std::endl;
    for (auto [key, value]: result) {
        benchmark_out << std::setw(25) << key;
        for (const auto t: value){
            benchmark_out << std::setw(20) << t;
        }
        benchmark_out << std::endl;
    }
    benchmark_out.close();
    return 0;
}
