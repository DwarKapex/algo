#include "Sorts.h"
#include <Tester.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <memory>

namespace fs = std::filesystem;
std::filesystem::path this_file = __FILE__;
constexpr size_t NAME_FIELD_SIZE = 15;
constexpr size_t NUMBER_FIELD_SIZE = 10;

void benchmark(const std::string& test_name,
               std::ofstream& output) {
    
    
//        OtusAlgo::BubbleSort b_sort;

    std::vector<std::shared_ptr<OtusAlgo::Sort>> all_sorts{
                // too slow
//                std::make_shared<OtusAlgo::BubbleSort>(),
                std::make_shared<OtusAlgo::SelectionSort>(),
                std::make_shared<OtusAlgo::InsertionSort>(),
                // original sequence
                std::make_shared<OtusAlgo::ShellSort>(),
                // Knuth sequence
                std::make_shared<OtusAlgo::ShellSort>(std::vector<size_t>{7174453, 2391484, 797161, 265720,
                                                        88573, 29524, 9841, 3280, 1093,
                                                        363, 121, 40,13,4, 1}),
                // Latest, experimentally derived
                std::make_shared<OtusAlgo::ShellSort>(std::vector<size_t>{701, 301, 132, 57, 23, 10, 4, 1}),
                std::make_shared<OtusAlgo::HeapSort>(),

        
    };
    std::vector<std::string> sort_names{"SelectionSort", "InsertionSort", "ShellSortBasic",
                                        "ShellSortKnuth", "ShellSortLatest", "HeapSort"};
//    OtusAlgo::BubbleSort b_sort;
//    OtusAlgo::SelectionSort s_sort;
//    OtusAlgo::InsertionSort i_sort;
    
    output << test_name << "\n";
    for (size_t i = 0; i < all_sorts.size(); ++i) {
        OtusAlgo::Tester test(*all_sorts[i], this_file.parent_path().string() + "/tests/" + test_name);
        auto times = test.RunTests(5);
        output << std::setw(NAME_FIELD_SIZE) << sort_names[i];
        for (const size_t t: times) {
            output << std::setw(NUMBER_FIELD_SIZE) << t;
        }
        output << std::endl;
    }
    
}

    
int main() {
    // for tests
    // elapsed time to save
    std::ofstream output(this_file.parent_path().string() + "/benchmark.txt");

    size_t n = 1;
    output << std::setw(NAME_FIELD_SIZE) << "array size";
    for (int i = 0; i <= 5; ++i) {
        output << std::setw(NUMBER_FIELD_SIZE) << n;
        n *= 10;
    }
    output << std::endl;
    // random
    benchmark("0.random", output);
    // digits
    benchmark("1.digits", output);
    // sorted
    benchmark("2.sorted", output);
    // revers
    benchmark("3.revers", output);



    return 0;
}
