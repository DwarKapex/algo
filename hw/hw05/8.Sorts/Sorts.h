#pragma once

#include <ITask.h>
#include <vector>
namespace OtusAlgo {

class Sort: public ITask {
public:
    using IntType = uint64_t;
    std::string Run(const ITask::DataType&) override;
    virtual void DoSort(std::vector<IntType>&) = 0;
};


class BubbleSort: public Sort {
public:
    void DoSort(std::vector<IntType>&) override;
};

class SelectionSort: public Sort {
public:
    void DoSort(std::vector<IntType>&) override;
};

class InsertionSort: public Sort {
public:
    void DoSort(std::vector<IntType>&) override;
};


class ShellSort: public Sort {
public:
    ShellSort() = default;
    ShellSort(std::vector<size_t> steps);
    void DoSort(std::vector<IntType>&) override;
private:
    std::vector<size_t> m_steps;
};

class HeapSort: public Sort {
public:
    void DoSort(std::vector<IntType>&) override;
private:
    void Heapify(std::vector<IntType>&, size_t, size_t);
};


} //namespace OtusAlgo

