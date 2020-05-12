#pragma once

#include <ITask.h>

namespace OtusAlgo {

class Primes: public ITask {
public:
    using IntType = uint64_t;
    std::string Run(const ITask::DataType&) override;
    virtual IntType Calculate(IntType a) const = 0;
};

class PrimesDividers: public Primes {
public:
    IntType Calculate(IntType a) const override;
    bool IsPrime(IntType a) const;
};

class PrimesDividers2: public Primes {
public:
    IntType Calculate(IntType a) const override;
};

class PrimesSieve: public Primes {
public:
    IntType Calculate(IntType a) const override;
};

class PrimesSieveBitmap: public Primes {
public:
    IntType Calculate(IntType a) const override;
private:
    size_t GetBitOneCount(int a) const;
};

class PrimesSieveN: public Primes {
public:
    IntType Calculate(IntType a) const override;
};


} //namespace OtusAlgo

