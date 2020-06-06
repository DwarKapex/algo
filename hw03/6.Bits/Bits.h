#pragma once

#include <ITask.h>
#include <vector>
#include <optional>

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
    IntType RookMoves(const std::string&, char);
    IntType BishopMoves(const std::string&, char);
    IntType QueenMoves(const std::string&, char);

private:
    IntType FindPiecePos(const std::string& fen, char piece);
    
    std::optional<bool> IsBittable(IntType pos, char piece);
    void UpdateMask(IntType& mask, int pos, int step, int max_steps);
};


} //namespace OtusAlgo

