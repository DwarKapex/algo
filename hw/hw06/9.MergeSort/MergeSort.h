#pragma once

#include <fstream>
#include <filesystem>
#include <algorithm>
#include <vector>

#include <iostream>

namespace OtusAlgo {

template<typename Int = uint16_t>
class IChunkSort {
public:
    virtual void sort(std::vector<Int>&) = 0;
};

template<typename Int = uint16_t>
class QuickSortChunk: public IChunkSort<Int> {
public:
    void sort(std::vector<Int>& data) override {
        std::sort(data.begin(), data.end());
    }
};


template<typename Int = uint16_t>
class MergeSortChunk: public IChunkSort<Int> {
public:
    void sort(std::vector<Int>& data) override {
        sort_helper(data, 0, data.size()-1);
    }
private:
    void sort_helper(std::vector<Int>& data, size_t left, size_t right) {
        if (left < right) {
            size_t mid = left + (right - left) / 2;
            sort_helper(data, left, mid);
            sort_helper(data, mid+1, right);
            merge(data, left, mid, right);
        }
    }
    void merge(std::vector<Int>& data, size_t left, size_t mid, size_t right) {
        size_t n1 = mid - left + 1, n2 = right - mid;
        std::vector<Int> l(n1), r(n2);
        // copy data
        for (size_t i = 0; i < n1; ++i) {
            l[i] = data[left+i];
        }
        for (size_t i = 0; i < n2; ++i) {
            r[i] = data[mid+1+i];
        }
        size_t i=0,j=0,k = left;
        while (i < n1 && j < n2) {
            if (l[i] < r[j]) {
                data[k++] = l[i++];
            }
            else {
                data[k++] = r[j++];
            }
        }
        while (i < n1) {
            data[k++] = l[i++];
        }
        while (j < n2) {
            data[k++] = r[j++];
        }
    }
};



template<typename Int = uint16_t>
class MergeSort {
public:
    MergeSort(const std::filesystem::path& fpath, IChunkSort<Int>& chunk_sort, size_t chunk_size = 32):
          m_fpath(fpath)
        , m_chunk_size (chunk_size)
        , m_bytes(sizeof(Int))
        , m_chunk_sort(chunk_sort)
    {}
    
    
    void sort() {
        std::fstream input(m_fpath.string(), std::ios::in | std::ios::out |std::ios::binary);
        if (input) {
            input.seekg(0, std::ios::end);
            size_t size = input.tellg();
            sort_helper(input, 0, size/m_bytes - 1);
        }
        else
            throw std::runtime_error("Cannot open the file");
    }

private:
    void sort_helper(std::fstream& fname, size_t left, size_t right) {
        if (left < right) {
            if (right - left < m_chunk_size) {
                std::vector<Int> data(right-left+1, 0);
                fname.seekg(left*m_bytes, std::ios::beg);
                fname.read(reinterpret_cast<char*>(data.data()), (right-left+1)*m_bytes);
                m_chunk_sort.sort(data);
                fname.seekp(left*m_bytes, std::ios::beg);
                fname.write(reinterpret_cast<char*>(data.data()), (right-left+1)*m_bytes);
            }
            else {
                size_t mid = left + (right - left) / 2;
                sort_helper(fname, left, mid);
                sort_helper(fname, mid+1, right);
                merge(fname, left, mid, right);
            }
        }
    }
    void merge(std::fstream& fname, size_t left, size_t mid, size_t right) {
        size_t n1 = mid - left + 1, n2 = right - mid;
        size_t i = 0,j = 0;
        // copy data
        std::fstream m_L("/tmp/merge_left.txt",   std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc),
        m_R("/tmp/merge_right.txt",  std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

        if (!m_L || !m_R) {
            throw std::runtime_error("Cannot open left file");
        }
        fname.seekg(left*m_bytes, std::ios::beg);
        Int tmp;
        // copy left part of the range
        for (i = 0; i < n1; ++i) {
            fname.read(reinterpret_cast<char*>(&tmp), m_bytes);
            m_L.write(reinterpret_cast<char*>(&tmp), m_bytes);
        }
        m_R.seekp(0, std::ios::beg);
        for (j = 0; j < n2; ++j) {
            fname.read(reinterpret_cast<char*>(&tmp), m_bytes);
            m_R.write(reinterpret_cast<char*>(&tmp), m_bytes);
        }
        // merge
        fname.seekp(left*m_bytes, std::ios::beg);
        m_L.seekg(0, std::ios::beg);
        m_R.seekg(0, std::ios::beg);
        i = j = 0;
        Int l = 0, r = 0;
        if (i < n1 && j < n2) {
            m_L.read(reinterpret_cast<char*>(&l), m_bytes);
            m_R.read(reinterpret_cast<char*>(&r), m_bytes);
        }
        while (i < n1 && j < n2) {
            if (l < r) {
                fname.write(reinterpret_cast<char*>(&l), m_bytes);
                ++i;
                m_L.read(reinterpret_cast<char*>(&l), m_bytes);
            }
            else {
                fname.write(reinterpret_cast<char*>(&r), m_bytes);
                ++j;
                m_R.read(reinterpret_cast<char*>(&r), m_bytes);
            }
        }
        while (i < n1) {
            fname.write(reinterpret_cast<char*>(&l), m_bytes);
            ++i;
            m_L.read(reinterpret_cast<char*>(&l), m_bytes);
        }
        while (j < n2) {
            fname.write(reinterpret_cast<char*>(&r), m_bytes);
            ++j;
            m_R.read(reinterpret_cast<char*>(&r), m_bytes);
        }
    }
private:
    std::filesystem::path m_fpath;
    size_t m_chunk_size;
    const size_t m_bytes;
    IChunkSort<Int>& m_chunk_sort;
};


//а. Блочная сортировка.
template<typename Int = uint16_t>
class BucketSort {
public:
    void sort(std::vector<Int>& data) {
        constexpr size_t buckets_count = 5;
        std::vector<std::vector<Int>> buckets(buckets_count);
        constexpr size_t bucket_capacity = std::numeric_limits<Int>::max()/buckets_count + 1;
        for (const auto item: data) {
            size_t bucket_n = item / bucket_capacity;
            buckets[bucket_n].push_back(item);
        }
        for (size_t i = 0; i < buckets_count; ++i){
            std::sort(buckets[i].begin(), buckets[i].end());
        }
        auto it = data.begin();
        for (const auto& l: buckets) {
            std::copy(l.begin(), l.end(), it);
            std::advance(it, l.size());
        }
    }
};

//б. Сортировка подсчётом.
template<typename Int = uint16_t>
class CountingSort {
public:
    void sort(std::vector<Int>& data) {
        constexpr size_t n = std::numeric_limits<Int>::max()+1;
        std::vector<size_t> count(n, 0);
        for (const auto d: data) {
            ++count[d];
        }
        size_t k = 0;
        for (size_t i = 0; i < n; ++i) {
            size_t p = count[i];
            while (p > 0) {
                data[k++] = i;
                --p;
            }
        }
    }
};

//в. Поразрядная сортировка.
template<typename Int = uint16_t>
class RedixSort {
public:
    void sort(std::vector<Int>& data) {
        constexpr size_t n = 10;
        std::vector<size_t> count(n, 0);
        std::vector<Int> additional(data.size(),0);
        Int max = *std::max_element(data.begin(), data.end());
        size_t base = 1;
        while (max > 0) {
            count.assign(n, 0);
            // count digits
            for (const auto item: data) {
                size_t digit = (item / base) % 10;
                ++count[digit];
            }
            // sum up
            for (size_t i = 1; i < n; ++i) {
                count[i] += count[i-1];
            }
            //rearrange
            for (auto item = data.rbegin(); item != data.rend(); ++item) {
                size_t digit = (*item / base) % 10;
                additional[count[digit]-1] = *item;
                --count[digit];
            }
            data.swap(additional);
            // update limits
            max /= 10;
            base *=10;
        }
    }
};





} //namespace OtusAlgo

