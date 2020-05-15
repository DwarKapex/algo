#include "Bits.h"
#include <iostream>
#include <sstream>
#include <cctype>
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
    return std::to_string(WhiteRookMoves(fen));
}

auto BitStrickers::WhiteRookMoves(const std::string& fen) -> IntType {
    // find white rook
    size_t rook_pos = FindPiecePos(fen, 'R');
    
    IntType rook_mask = 1UL << rook_pos;
    // up
    int step = 8;
    IntType pos = rook_mask >> step;
    while(pos != 0) {
        if (m_board[rook_pos]) {
            
        }
        else {
            rook_mask |= pos;
            pos >>= step;
        }
        
    }
    return rook_mask;
}

auto BitStrickers::IsBittable(IntType pos, char piece) -> bool {
    // by default it piece is white
    size_t start = Piece::blackPawns,
           end = Piece::whiteKing;

    if (piece != std::tolower(piece)) {
        start = Piece::blackPawns;
        end = Piece::blackPawns;
    }
    for (size_t i = start; i <= end; ++i) {
        if (pos & m_board[i]) {
            return true;
        }
    }
    return false;
}


auto BitStrickers::FindPiecePos(const std::string& fen, char piece) -> IntType {
    IntType pos = 9223372036854775808UL;
    // move it to the beginning of the row
    IntType piece_pos = pos >> 7;
    size_t move;
    for (const auto item: fen) {
        move = 1;
        if (item == '/') {
            pos >>=8;
            piece_pos = pos >> 7;
            move = 0;
        }
        else if (item == piece) {
            return piece_pos;
        }
        else {
            move = int(item-'0');
        }
        piece_pos <<= move;
    }
    return 0;
}

} //namespace OtusAlgo
