#pragma once

#include <ITask.h>

namespace OtusAlgo {

class Fibo: public ITask {
public:
    using IntType = uint64_t;
    std::string Run(const ITask::DataType&) override;
    virtual IntType Calculate(IntType N) const = 0;
};

class FiboRecursive: public Fibo {
public:
    IntType Calculate(IntType N) const override;
};

class FiboIter: public Fibo {
public:
    IntType Calculate(IntType N) const override;
};

class FiboGolden: public Fibo {
public:
    IntType Calculate(IntType N) const override;
};

class FiboMatrix: public Fibo {
public:
    using MatrixType = std::vector<IntType>;
    IntType Calculate(IntType N) const override;
private:
    MatrixType PowerMatrix(IntType n) const ;
    MatrixType MultiplyMatrix(MatrixType a, MatrixType b) const;
    MatrixType m_matrix = {1,1,1,0};
};


} //namespace OtusAlgo

