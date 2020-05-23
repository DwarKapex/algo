#include "BasicStructures.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

template <typename T>
void benchmark_add(std::ofstream& output, OtusAlgo::IArray<T>& array, std::string name) {
    output << name << '\t';
    constexpr size_t INSERT_ELEMENTS = 100000;
    // singe_array
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < INSERT_ELEMENTS; ++i) {
        array.add(i);
    }
    auto end = std::chrono::system_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    output << us << " us\n";

}

template <typename T>
void benchmark_insert_random(std::ofstream& output, OtusAlgo::IArray<T>& array, std::string name) {
    output << name << '\t';
    constexpr size_t INSERT_ELEMENTS = 10000;
    std::vector<size_t> insert_pos;
    for (int i = 0; i < INSERT_ELEMENTS; ++i) {
        insert_pos.push_back((i*7 + 13) % 100000);
    }
    // singe_array
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < INSERT_ELEMENTS; ++i) {
        array.add(i, insert_pos[i]);
    }
    auto end = std::chrono::system_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    output << us << " ms\n";
}

template <typename T>
void benchmark_remove_random(std::ofstream& output, OtusAlgo::IArray<T>& array, std::string name) {
    output << name << '\t';
    constexpr size_t REMOVE_ELEMENTS = 10000;
    std::vector<size_t> remove_pos;
    for (int i = 0; i < REMOVE_ELEMENTS; ++i) {
        remove_pos.push_back((i*13 + 7) % array.size() - REMOVE_ELEMENTS);
    }
    // singe_array
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < REMOVE_ELEMENTS; ++i) {
        array.remove(remove_pos[i]);
    }
    auto end = std::chrono::system_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    output << us << " ms\n";

}


template <typename T>
void benchmark_get_random(std::ofstream& output, OtusAlgo::IArray<T>& array, std::string name) {
    output << name << '\t';
    constexpr size_t INSERT_ELEMENTS = 10000;
    std::vector<size_t> get_pos;
    for (int i = 0; i < INSERT_ELEMENTS; ++i) {
        get_pos.push_back((i*13 + 7) % array.size());
    }
    // singe_array
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < INSERT_ELEMENTS; ++i) {
        array.get(get_pos[i]);
    }
    auto end = std::chrono::system_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    output << us << " ms\n";

}


int main() {
    OtusAlgo::SingleArray<int> single_array;
    OtusAlgo::VectorArray<int> vector_array;
    OtusAlgo::FactorArray<int> factor_array;
    OtusAlgo::VectorWrapper<int> vector_wrapper;

    std::filesystem::path this_file = __FILE__;
    std::ofstream output(this_file.parent_path().string() + "/benchmark.txt");

    // benchmark
    // insert back
//    output << "Adding back 1000000 elements:\n";
    benchmark_add(output, single_array, "Single Array");
    benchmark_add(output, vector_array, "Vector Array");
    benchmark_add(output, factor_array, "Factor Array");
    benchmark_add(output, vector_wrapper, "Vector Wrapper");


    // insert random
    output << "\nInserting at random position 10000 times:\n";
    benchmark_insert_random(output, single_array, "Single Array");
    benchmark_insert_random(output, vector_array, "Vector Array");
    benchmark_insert_random(output, factor_array, "Factor Array");
    benchmark_insert_random(output, vector_wrapper, "Vector Wrapper");

    output << "\nRemoving at random position 10000 times:\n";
    benchmark_remove_random(output, single_array, "Single Array");
    benchmark_remove_random(output, vector_array, "Vector Array");
    benchmark_remove_random(output, factor_array, "Factor Array");
    benchmark_remove_random(output, vector_wrapper, "Vector Wrapper");

    //
    output << "\nGetting element at random position 10000 times:\n";
    benchmark_get_random(output, single_array, "Single Array");
    benchmark_get_random(output, vector_array, "Vector Array");
    benchmark_get_random(output, factor_array, "Factor Array");
    benchmark_get_random(output, vector_wrapper, "Vector Wrapper");


    output << "\nSummary: using basic data structure such as array has both advantages and disadvantages."
              "Advantages is obvious: element access time is O(1) because array is places as a continous "
              "set of elements in RAM. Disadvantages: when the size of the array exceeds the capacity, we "
              "need to reallocate more memory not only for a new elemnts, but for all elements in array, "
              "copy all elements to a new place and only after that add new element. That takes time for"
              " sure (on avarage O(n), where n is size of array). And less frequently we do that, more efficient "
              "data structure we have. The same for removing and inserting elements in the middle: to keep data "
              "structured continuesly in RAM, we have to copy all elements from inserting index. So on avarage "
              "it is O(n) copying operations.";


    // PriorityQueue
    OtusAlgo::PrioretyQueue<int> pq;
    pq.enqueue(1, 10);
    pq.enqueue(2, 20);
    pq.enqueue(7, 30);
    pq.enqueue(3, 40);
    pq.enqueue(7, 50);
    pq.enqueue(1, 60);

    std::string res = "";
    for (int i = 0; i < 6; ++i) {
        res += std::to_string(pq.dequeue()) + " ";
    }

    std::string expected = "30 50 40 20 10 60 ";
    std::cout << "PriorityQueue output: " << res << " ; is equal to expected: " << std::boolalpha << (res == expected) << std::endl;
    
    // Sparce Matrix
    constexpr int def_value = 0;
    OtusAlgo::Matrix<int, def_value, 2> matrix;
    const int N = 10;
    
    auto a = matrix[0][0];
    
    for (int i = 0; i < N; ++i)
        matrix[i][i] = matrix[N-1-i][i] = i;

    // chess order fill-in
    for (size_t row = 0; row < N/2; ++row) {
        for (size_t col = 0; col < N; col+=2){
            matrix[2*row+1][col+1] = matrix[2*row][col] = def_value;
        }
    }

    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col){
            std::cout << matrix[row][col];
            if (col == 8) std::cout << std::endl;
            else std::cout << " ";
        }
    }
    std::cout << matrix.size() << std::endl;
    
    for (const auto& [key, value]: matrix){
        std::string t;
        for (const auto& c: key) {
            t += std::to_string(c) + " ";
        }
        t = t.substr(0, t.size()-1);
        std::cout << "[" <<  t << "] : " << value << std::endl;
    }
    
    return 0;
}
