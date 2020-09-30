#include <fstream>
#include <filesystem>

#include <iostream>

namespace OtusAlgo {

void ClassicMerge(std::fstream& fname, size_t left, size_t middle, size_t right) {

    // copy data to temp file
    std::fstream f1("merge_sort_left",  std::ios::binary | std::ios::in | std::ios::out),
                 f2("merge_sort_right", std::ios::binary | std::ios::in | std::ios::out);
    constexpr size_t bytes = sizeof(uint16_t);
    uint16_t data = 0;
    fname.seekg(left*bytes,std::ios::beg);
    for (size_t i =  left; i < middle + 1; ++i) {
        uint16_t data = 0;
        fname.read(reinterpret_cast<char*>(&data), bytes);
        f1.write(reinterpret_cast<char*>(&data), bytes);
    }
    fname.seekg((middle+1)*bytes,std::ios::beg);
    for (size_t i =  middle + 1; i < right ; ++i) {
        fname.read(reinterpret_cast<char*>(&data), bytes);
        f2.write(reinterpret_cast<char*>(&data), bytes);
    }
    // merge sorted parts to original array
    fname.seekp(left*bytes,std::ios::beg);
//    f1.seekg(0, std::ios::beg);
//    f2.seekg(0, std::ios::beg);
    uint16_t l, r;
    if (!f1.eof() && !f2.eof()) {
        f1.read(reinterpret_cast<char*>(&l), bytes);
        f2.read(reinterpret_cast<char*>(&r), bytes);
    }

    do {
        if (l < r) {
            fname.write(reinterpret_cast<char*>(&l), bytes);
            f1.read(reinterpret_cast<char*>(&l), bytes);
        }
        else {
            fname.write(reinterpret_cast<char*>(&r), bytes)
            f2.read(reinterpret_cast<char*>(&r), bytes);
        }

    } while (!f1.eof() && !f2.eof());

    while (!f1.eof()) {
        fname.write(reinterpret_cast<char*>(&l), bytes);
        f1.read(reinterpret_cast<char*>(&l), bytes);
    }
    while (!f2.eof()) {
        fname.write(reinterpret_cast<char*>(&r), bytes);
        f2.read(reinterpret_cast<char*>(&r), bytes);
    }



}

void ClassicMergeSort(std::fstream& fname, size_t left, size_t right) {
    if (left >= right)
        return;
    size_t middle = left + (right - left) / 2;
    ClassicMergeSort(fname, left, middle);
    ClassicMergeSort(fname, middle+1, right);
    ClassicMerge(fname, left, middle, right);
}


} //namespace OtusAlgo
