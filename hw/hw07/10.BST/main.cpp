#include "BST.h"
#include "AVL.h"
#include <iostream>
#include <memory>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <random>

namespace fs = std::filesystem;
fs::path this_file = __FILE__;


void SimpleBST_benchmark() {
    std::ofstream bench_output((this_file.parent_path() / "bst_benchmark.txt").string(), std::ios::out);

    // fill out test values
    constexpr size_t N = 50000;
    bench_output << "Insert " << N << " numbers in range [0:" << N-1 << "]\n\n";
    std::vector<int> values(N, 0);
    std::iota(values.begin(), values.end(), 0);

    OtusAlgo::BST sorted_insert;
    auto start = std::chrono::system_clock::now();
    for (const int value: values)
        sorted_insert.insert(value);
    auto end = std::chrono::system_clock::now();
    auto diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Sorted insert: " << diff_msec << " ms\n";

    OtusAlgo::BST random_insert;
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(values.begin(), values.end(), rng);

    start = std::chrono::system_clock::now();
    for (const int value: values){
        random_insert.insert(value);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Random insert: " << diff_msec << " ms\n\n";

    // Search N/10
    bench_output << "Search " << N/10 << " random numbers:\n";
    std::shuffle(values.begin(), values.end(), rng);

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < N/10; ++i){
        sorted_insert.search(values[i]);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Sorted tree search: " << diff_msec << " ms\n\n";

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < N/10; ++i){
        random_insert.search(values[i]);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Random tree search: " << diff_msec << " ms\n\n";

    // Delete N/10
    bench_output << "Remove " << N/10 << " random numbers:\n";
    std::shuffle(values.begin(), values.end(), rng);

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < N/10; ++i){
        sorted_insert.remove(values[i]);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Sorted tree remove: " << diff_msec << " ms\n\n";

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < N/10; ++i){
        random_insert.remove(values[i]);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Random tree remove: " << diff_msec << " ms\n\n";

    bench_output << "Summary: inserting (searching and removing) sorted values, we get result similar to list by EOD"
                 << " and insertion takes O(N). Inserting random numbers is insertion with "
                 << "O(log(N)) time complexity";
    bench_output.close();
}

void AVL_benchmark() {
    std::ofstream bench_output((this_file.parent_path() / "avl_benchmark.txt").string(), std::ios::out);
    

    // fill out test values
    constexpr size_t N = 10000;
    bench_output << "Insert " << N << " numbers in range [0:" << N-1 << "]\n\n";
    std::vector<int> values(N, 0);
    std::iota(values.begin(), values.end(), 0);

    OtusAlgo::AVL sorted_insert;
    auto start = std::chrono::system_clock::now();
    for (const int value: values)
        sorted_insert.insert(value);
    auto end = std::chrono::system_clock::now();
    auto diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Sorted insert: " << diff_msec << " ms\n";

    OtusAlgo::AVL random_insert;
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(values.begin(), values.end(), rng);

    start = std::chrono::system_clock::now();
    for (const int value: values){
        random_insert.insert(value);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Random insert: " << diff_msec << " ms\n\n";

    // Search N/10
    bench_output << "Search " << N/10 << " random numbers:\n";
    std::shuffle(values.begin(), values.end(), rng);

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < N/10; ++i){
        sorted_insert.search(values[i]);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Sorted tree search: " << diff_msec << " ms\n\n";

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < N/10; ++i){
        random_insert.search(values[i]);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Random tree search: " << diff_msec << " ms\n\n";

    // Delete N/10
    bench_output << "Remove " << N/10 << " random numbers:\n";
    std::shuffle(values.begin(), values.end(), rng);

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < N/10; ++i){
        sorted_insert.remove(values[i]);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Sorted tree remove: " << diff_msec << " ms\n\n";

    start = std::chrono::system_clock::now();
    for (size_t i = 0; i < N/10; ++i){
        random_insert.remove(values[i]);
    }
    end = std::chrono::system_clock::now();
    diff_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    bench_output << "Random tree remove: " << diff_msec << " ms\n\n";

    bench_output << "Summary: it does not matter what you insert into AVL tree: rebalance always fixes "
                 << "the order and keep the tree as BST, but every rebalancing makes AVL removing/insertion slower"
                 << " with respect to simple BST";
    bench_output.close();

}

    
int main() {
//    SimpleBST_benchmark();
    AVL_benchmark();
    return 0;
}
