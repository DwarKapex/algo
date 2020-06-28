#pragma once

#include <ITask.h>

namespace OtusAlgo {

class GCD: public ITask {
public:
    using IntType = uint64_t;
    std::string Run(const ITask::DataType&) override;
    virtual IntType Calculate(IntType a, IntType b) const = 0;
};

class EuclidSub: public GCD {
public:
    IntType Calculate(IntType a, IntType b) const override;
};

class EuclidMod: public GCD {
public:
    IntType Calculate(IntType a, IntType b) const override;
};

class Stein: public GCD {
public:
    IntType Calculate(IntType a, IntType b) const override;
};


} //namespace OtusAlgo

