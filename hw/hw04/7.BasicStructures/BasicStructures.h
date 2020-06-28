#pragma once

#include <cstring>
#include <vector>
#include <list>
#include <stdexcept>      // std::out_of_range
#include <algorithm>
#include <memory>
#include "SparceMatrix.h"

namespace OtusAlgo {

template <typename T>
class IArray {
public:
    IArray() = default;
    virtual ~IArray() = default;
     
    virtual void add(T item) = 0;
    virtual size_t size() const noexcept = 0;
    virtual void add(T item, int index) = 0;
    virtual T get(int index) const noexcept = 0;
    virtual T remove(int index) = 0;
};


template <typename T>
class SingleArray: public IArray<T> {
public:
    SingleArray() = default;
    ~SingleArray() {
        delete [] m_array;
    }

    void add(T item) noexcept override {
        resize();
        m_array[m_size - 1] = item;
    }
    
    size_t size() const noexcept override { return m_size; }

    void add(T item, int index) override  {
        add(item);
        size_t idx = m_size-1;
        while (idx > index) {
            m_array[idx] = m_array[idx-1];
            --idx;
        }
        m_array[index] = item;
    }

    T get (int index) const noexcept override {
        if (out_of_boarder(index))
            return {};
        return m_array[index];
    }
    
    T remove(int index) override {
        if (out_of_boarder(index)) {
            return {};
        }
        for (size_t i = index; i < m_size-1; ++i) {
            m_array[i] = m_array[i+1];
        }
        --m_size;
        return {};
    }

private:
    void resize() {
            T* new_array = new T[size() + 1];
            std::memcpy(new_array, m_array, size());
            delete [] m_array;
            ++m_size;
            m_array = new_array;
    }
    bool out_of_boarder(size_t index) const {
        if (index >= size() || index < 0)
            return true;
        return false;
    }
    size_t m_size = 0;
    T* m_array = nullptr;
};


template <typename T>
class VectorArray: public IArray<T> {
public:
    VectorArray() = default;
    VectorArray(int expand_step): m_expand_step(expand_step) {}

    ~VectorArray() { delete [] m_array; }

    void add(T item) noexcept override {
        resize();
        m_array[m_size - 1] = item;
    }

    size_t size() const noexcept override { return m_size; }

    void add(T item, int index) override  {
        add(item);
        size_t idx = m_size-1;
        while (idx > index) {
            m_array[idx] = m_array[idx-1];
            --idx;
        }
        m_array[index] = item;
    }

    T get (int index) const noexcept override {
        if (out_of_boarder(index))
            return {};
        return m_array[index];
    }
    
    T remove(int index) override {
        if (out_of_boarder(index)) {
            return {};
        }
        for (size_t i = index; i < m_size-1; ++i) {
            m_array[i] = m_array[i+1];
        }
        --m_size;
        return {};
    }

private:
    bool out_of_boarder(size_t index) const {
        if (index >= size() || index < 0)
            return true;
        return false;
    }

    void resize() {
            T* new_array = new T[size() + m_expand_step];
            std::memcpy(new_array, m_array, size());
            delete [] m_array;
            ++m_size;
            m_array = new_array;
    }
    size_t m_expand_step = 10;
    T* m_array = nullptr;
    size_t m_size = 0;
};


template <typename T>
class FactorArray: public IArray<T> {
public:
    FactorArray() = default;
    ~FactorArray() { delete [] m_array; }

    void add(T item) noexcept override {
        resize();
        m_array[m_size - 1] = item;
    }

    size_t size() const noexcept override { return m_size; }
    
    T get (int index) const noexcept override {
        if (out_of_boarder(index))
            return {};
        return m_array[index];
    }
    
    void add(T item, int index) override  {
        add(item);
        size_t idx = m_size-1;
        while (idx > index) {
            m_array[idx] = m_array[idx-1];
            --idx;
        }
        m_array[index] = item;
    }

    T remove(int index) override {
        if (out_of_boarder(index)) {
            return {};
        }
        for (size_t i = index; i < m_size-1; ++i) {
            m_array[i] = m_array[i+1];
        }
        --m_size;
        return {};
    }

private:
    bool out_of_boarder(size_t index) const {
        if (index >= size() || index < 0)
            return true;
        return false;
    }
    void resize() {
        ++m_size;
        if (m_size >= m_capacity) {
            m_capacity = m_capacity*m_expand_factor + 1;
            T* new_array = new T[m_capacity];
            std::memcpy(new_array, m_array, m_size-1);
            delete [] m_array;
            m_array = new_array;
        }
    }
private:
    T* m_array = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
    size_t m_expand_factor = 2;
};

template <typename T>
class VectorWrapper: public IArray<T> {
public:
    void add(T item) noexcept override {
        m_array.push_back(item);
    }

    size_t size() const noexcept override { return m_array.size(); }
    
    T get (int index) const noexcept override {
        return m_array.at(index);
    }
    
    void add(T item, int index) override  {
        m_array.insert(m_array.begin() + index, item);
    }

    T remove(int index) override {
        m_array.erase(m_array.begin() + index);
    }

private:
    std::vector<T> m_array;
};

template<typename T>
class PrioretyQueue {
    using Queue = std::vector<std::list<T>>;
public:
    void enqueue(int priority, T item) {
        if (!is_priority_correct(priority)) return;
        if (priority+1 > m_queue.size()) {
            m_queue.resize(priority + 1);
        }
        m_queue[priority].push_back(item);
    }
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("No more elements to dequeue. The queue is empty.");
        }
        T result = m_queue.back().front();
        m_queue.back().pop_front();
        while (!m_queue.empty() && m_queue.back().size() == 0) {
            m_queue.pop_back();
        }
        return result;
    }
    
    size_t size() noexcept { return m_queue.size(); }
    bool empty() noexcept { return size() == 0; }
private:
    bool is_priority_correct(int priority) { return priority > 0; }
    Queue m_queue;
};

} //namespace OtusAlgo

