#pragma once

#include <ITask.h>

namespace OtusAlgo {

enum Piece : int
{
    whitePawns = 0,
    whiteKnights,
    whiteBishops,
    whiteRooks,
    whiteQueens,
    whiteKing,

    blackPawns,
    blackKnights,
    blackBishops,
    blackRooks,
    blackQueens,
    blackKing
};

class Bits: public ITask {
public:
    using IntType = uint64_t;
    std::string Run(const ITask::DataType&) override;
    size_t GetOneBitCount(IntType a);
    virtual IntType Calculate(IntType a) const = 0;
};


class BitKing: public Bits {
public:
    IntType Calculate(IntType a) const override;
};

class BitKnight: public Bits {
public:
    IntType Calculate(IntType a) const override;
};

class BitFEN: public ITask {
public:
    std::string Run(const ITask::DataType&) override;
};

class BitStrickers: public Bits {
public:
    IntType Calculate(IntType a) const override;
};


} //namespace OtusAlgo

