#pragma once

#include <ITask.h>
#include <vector>
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
    using IntType = uint64_t;
    using BoardType = std::vector<IntType>;
    std::string Run(const ITask::DataType&) override;
    void PlacePieces(const std::string&);
protected:
    BoardType m_board = BoardType(12,0);
};

class BitStrickers: public BitFEN {
public:
    std::string Run(const ITask::DataType&) override;
    IntType WhiteRookMoves(const std::string&);
private:
    IntType FindPiecePos(const std::string& fen, char piece);
    bool IsBittable(IntType pos, char piece);
};


} //namespace OtusAlgo

