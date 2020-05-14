#include "Bits.h"
#include <iostream>
#include <sstream>
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
    std::string fen = data.front();
    
    std::vector<uint64_t> board(12,0);
    // init position = 2^63
    uint64_t pos = 9223372036854775808UL;
    // move it to the beginning of the row
    uint64_t piece_pos = pos >> 7;
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
               board[Piece::whiteKing] |= piece_pos;
               break;

             case 'Q':
                 board[Piece::whiteQueens] |= piece_pos;
                 break;

              case 'R':
                  board[Piece::whiteRooks] |= piece_pos;
                  break;

              case 'B':
                  board[Piece::whiteBishops] |= piece_pos;
                  break;

              case 'N':
                  board[Piece::whiteKnights] |= piece_pos;
                  break;
                       
              case 'P':
                  board[Piece::whitePawns] |= piece_pos;
                  break;

              case 'k':
                  board[Piece::blackKing] |= piece_pos;
                  break;

              case 'q':
                   board[Piece::blackQueens] |= piece_pos;
                   break;

               case 'r':
                  board[Piece::blackRooks] |= piece_pos;
                  break;

               case 'b':
                   board[Piece::blackBishops] |= piece_pos;
                   break;

               case 'n':
                   board[Piece::blackKnights] |= piece_pos;
                   break;

               case 'p':
                   board[Piece::blackPawns] |= piece_pos;
                   break;

               default:
                   move = int(item-'0');
                   break;
        }
        piece_pos <<= move;
    }
    
    std::string res = "";
    for (const auto row: board) {
        res += std::to_string(row) + " ";
    }
    return res;
}

//auto BitStrickers::Calculate(IntType a) const -> IntType {
//    return {};
//}

} //namespace OtusAlgo
