#include "Sorts.h"
#include <iostream>
#include <sstream>
#include <algorithm>
namespace OtusAlgo {


std::string Sort::Run(const ITask::DataType& data) {
    if (data.size() < 2) {
        return "";
    }
    uint64_t n;
    n = std::stoll(data[0]);
    std::vector<IntType> arr;
    arr.reserve(n);
    
    IntType a;
    for (size_t i = 0; i < n; ++i) {
        std::stringstream ss(data[i+1]);
        ss >> a;
        arr.push_back(a);
    }
    DoSort(arr);
    std::stringstream res;
    for (size_t i = 0; i < arr.size(); ++i) {
        res << arr[i] << " ";
    }
    return res.str();
}


void BubbleSort::DoSort(std::vector<IntType>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size()-1; ++j){
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

void SelectionSort::DoSort(std::vector<IntType>& arr) {
    for (size_t i = 0; i < arr.size()-1; ++i) {
        size_t min_pos = i;
        IntType min = arr[i];
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < min){
                min = arr[j];
                min_pos = j;
            }
        }
        std::swap(arr[i], arr[min_pos]);
    }
}

void InsertionSort::DoSort(std::vector<IntType>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        IntType save = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > save) {
            arr[j+1] = arr[j];
            --j;
        }
        std::swap(arr[j+1], save);
    }
}

ShellSort::ShellSort(std::vector<size_t> steps):
            m_steps(std::move(steps)) {}

void ShellSort::DoSort(std::vector<IntType>& arr)  {
    bool original = false;
    if (m_steps.empty()) {
        original = true;
        size_t step = arr.size() / 2;
        while (step > 0) {
            m_steps.push_back(step);
            step /= 2;
        }
    }
    for (const auto step: m_steps) {
        for (int i = 0; i + step < arr.size(); ++i) {
            size_t j = i + step;
            IntType temp = arr[j];
            while ((j >= step) && (arr[j-step] > temp)) {
                arr[j] = arr[j-step];
                j -= step;
            }
            arr[j] = temp;
        }
    }
    if (original) {
        m_steps.clear();
    }
}

void HeapSort::DoSort(std::vector<IntType>& arr) {
    // make initial heap
    for (int j = arr.size()/2 - 1; j>=0; --j) {
        Heapify(arr, j, arr.size());
    }
    for (int j = arr.size()-1; j >=0; --j) {
        std::swap(arr[0], arr[j]);
        Heapify(arr, 0, j);
    }
}

void HeapSort::Heapify(std::vector<IntType>& arr, size_t root, size_t size) {
    size_t x = root;
    size_t l = 2*x + 1, r = 2*x + 2;
    if (l < size && arr[x] < arr[l]) x = l;
    if (r < size && arr[x] < arr[r]) x = r;
    if (x == root) return;
    std::swap(arr[root], arr[x]);
    Heapify(arr, x, size);
}

} //namespace OtusAlgo
