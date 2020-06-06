#include "Bits.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <optional>

namespace OtusAlgo {


std::string Bits::Run(const ITask::DataType& data) {
    if (data.empty()) {
        return "0";
    }
    IntType a;
    std::stringstream ss;
    ss << data[0];
    ss >> a;
    IntType result = Calculate(a);
    size_t bit_count = GetOneBitCount(result);
    std::string res = std::to_string(bit_count) + " "
               + std::to_string(result) + " ";
    return res;
}

size_t Bits::GetOneBitCount(IntType a) {
    size_t count = 0;
    while (a) {
        a &= (a-1);
        ++count;
    }
    return count;
}

auto BitKing::Calculate(IntType a) const -> IntType {
    uint64_t k = 1UL << a;
    uint64_t kL = k & 0xFEFEFEFEFEFEFEFE;
    uint64_t kR = k & 0x7F7F7F7F7F7F7F7F;
    uint64_t mask =
        (kL << 7)  | (k << 8) | ( kR << 9)  |
        (kL >> 1)             | ( kR << 1) |
        (kL >> 9)  | (k >> 8) | ( kR >> 7)  ;
    
    return mask;
}

auto BitKnight::Calculate(IntType a) const -> IntType {
    uint64_t k = 1UL << a;
    uint64_t kL1 = k & 0xFEFEFEFEFEFEFEFE;
    uint64_t kL2 = k & 0xFCFCFCFCFCFCFCFC;
    
    uint64_t kR1 = k & 0x7F7F7F7F7F7F7F7F;
    uint64_t kR2 = k & 0x3F3F3F3F3F3F3F3F;

    uint64_t mask =
               (kL1 << 15) | (kR1 << 17)  |
               (kL2 << 6)  | (kR2 << 10)  |
               (kR2 >> 6)  | (kL2 >> 10)  |
               (kL1 >> 17) | (kR1 >> 15)  ;
    
    return mask;
}

auto BitFEN::Run(const ITask::DataType& data) -> std::string {
    using OtusAlgo::Piece;
    if (data.empty()) {
        return "0";
    }
    
    PlacePieces(data.front());
    std::string res = "";
    for (const auto row: m_board) {
        res += std::to_string(row) + " ";
    }
    return res;
}

auto BitFEN::PlacePieces(const std::string& fen) -> void {
    // clean up afterprevious test
    m_board = BoardType(12,0);
    // init position = 2^63
    IntType pos = 9223372036854775808UL;
    // move it to the beginning of the row
    IntType piece_pos = pos >> 7;
    size_t move = 1;
    for (const auto item: fen) {
        move = 1;
        switch (item) {
            case '/':
                pos >>=8;
                piece_pos = pos >> 7;
                move = 0;
                break;
                
            case 'K':
               m_board[Piece::whiteKing] |= piece_pos;
               break;

             case 'Q':
                 m_board[Piece::whiteQueens] |= piece_pos;
                 break;

              case 'R':
                  m_board[Piece::whiteRooks] |= piece_pos;
                  break;

              case 'B':
                  m_board[Piece::whiteBishops] |= piece_pos;
                  break;

              case 'N':
                  m_board[Piece::whiteKnights] |= piece_pos;
                  break;
                       
              case 'P':
                  m_board[Piece::whitePawns] |= piece_pos;
                  break;

              case 'k':
                  m_board[Piece::blackKing] |= piece_pos;
                  break;

              case 'q':
                   m_board[Piece::blackQueens] |= piece_pos;
                   break;

               case 'r':
                  m_board[Piece::blackRooks] |= piece_pos;
                  break;

               case 'b':
                   m_board[Piece::blackBishops] |= piece_pos;
                   break;

               case 'n':
                   m_board[Piece::blackKnights] |= piece_pos;
                   break;

               case 'p':
                   m_board[Piece::blackPawns] |= piece_pos;
                   break;

               default:
                   move = int(item-'0');
                   break;
        }
        piece_pos <<= move;
    }
    
}

std::string BitStrickers::Run(const ITask::DataType& data) {
    using OtusAlgo::Piece;
    if (data.empty()) {
        return "0";
    }
    
    std::string fen = data.front();
    PlacePieces(fen);
    std::string res = "";
    for (const auto row: m_board) {
        res += std::to_string(row) + " ";
    }
    return //std::to_string(WhiteRookMoves(fen)) + " ";
    std::to_string(RookMoves(fen, 'R')) + " " + std::to_string(BishopMoves(fen, 'B')) + " " +
            std::to_string(QueenMoves(fen, 'Q')) + " ";
}

auto BitStrickers::RookMoves(const std::string& fen, char piece) -> IntType {
    // find white rook
    const int rook_pos = FindPiecePos(fen, piece);
    if (rook_pos < 0)
        return 0;
    IntType rook_mask = 0;// = 1UL << rook_pos;
    // down
    UpdateMask(rook_mask, rook_pos, -8, rook_pos/8);
    // up
    UpdateMask(rook_mask, rook_pos, 8, 7-rook_pos/8);
    // left
    UpdateMask(rook_mask, rook_pos, -1, rook_pos % 8);
    // right
    UpdateMask(rook_mask, rook_pos, 1, 7 - rook_pos % 8);

    return rook_mask;
}

auto BitStrickers::BishopMoves(const std::string& fen, char piece = 'B') -> IntType {
//    // find white bishop
    const int bishop_pos = FindPiecePos(fen, piece);
    if (bishop_pos < 0)
        return {};
    IntType bishop_mask = 0;// = 1UL << bishop_pos;
    // up-left
    UpdateMask(bishop_mask, bishop_pos, 7, std::min(bishop_pos % 8, 7 - bishop_pos/8));
    // up-right
    UpdateMask(bishop_mask, bishop_pos, 9, std::min(7 - bishop_pos % 8, 7 - bishop_pos/8));
    // down-left
    UpdateMask(bishop_mask, bishop_pos, -9, std::min(bishop_pos % 8, bishop_pos/8));
    // down-right
    UpdateMask(bishop_mask, bishop_pos, -7, std::min(7 - bishop_pos % 8, bishop_pos/8));

    return bishop_mask;

}

auto BitStrickers::QueenMoves(const std::string& fen, char piece) -> IntType {
    return RookMoves(fen, piece) | BishopMoves(fen, piece);
}

void BitStrickers::UpdateMask(IntType& mask, int pos, int step, int max_steps) {
    pos+=step;
    while(max_steps>0) {
        --max_steps;
        auto bittable = IsBittable(pos, 'R');
        if (bittable.has_value()) {
            if (bittable.value()) {
                mask |= (1UL << pos);
            }
            break;
        }
        else {
            mask |= (1UL << pos);
        }
        pos += step;
    }
}

auto BitStrickers::IsBittable(IntType pos, char piece) -> std::optional<bool> {
    // check white pieces on board
    for (size_t i = 0; i <= Piece::whiteKing; ++i) {
        if (m_board[i] & (1UL << pos)) {
            if (piece == std::tolower(piece)) {
                return {true};
            }
            else {
                return {false};
            }
        }
    }
    // check black pieces on board
    for (size_t i = Piece::blackPawns; i <= Piece::blackKing; ++i) {
        if (m_board[i] & (1UL << pos)) {
            if (piece == std::tolower(piece)) {
                return {false};
            }
            else {
                return {true};
            }
        }
    }
    return {};
}


auto BitStrickers::FindPiecePos(const std::string& fen, char piece) -> IntType {
    size_t pos_2 = 56;
    // move it to the beginning of the row
    size_t move;
    for (const auto item: fen) {
        move = 1;
        if (item == '/') {
            move = -16;
        }
        else if (item == piece) {
            return pos_2;
        }
        else if (int(item-'0') >=0 && int(item-'0') <= 9){
            move = int(item-'0');
        }
        pos_2 += move;
    }
    return -1;
}

} //namespace OtusAlgo
