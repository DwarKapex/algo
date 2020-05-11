#pragma once

#include <ITask.h>

namespace OtusAlgo {

class Power: public ITask {
public:
    using IntType = uint64_t;
    using FloatType = long double;
    std::string Run(const ITask::DataType&) override;
    virtual FloatType Calculate(FloatType a, IntType b) const = 0;
};

class PowerMultiplication: public Power {
public:
    FloatType Calculate(FloatType a, IntType b) const override;
};

class Power2: public Power {
public:
    FloatType Calculate(FloatType a, IntType b) const override;
};

class PowerBinary: public Power {
public:
    FloatType Calculate(FloatType a, IntType b) const override;
};


} //namespace OtusAlgo

