#include "Bits.h"
#include <Tester.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>

namespace fs = std::filesystem;

int main() {
    // for tests
    std::filesystem::path this_file = __FILE__;
    
//    {
//    OtusAlgo::BitKing king;
//    OtusAlgo::Tester test(king, this_file.parent_path().string() + "/tests/king");
//    test.RunTests();
//    }
//
//    {
//    OtusAlgo::BitKnight knight;
//    OtusAlgo::Tester test(knight, this_file.parent_path().string() + "/tests/knight");
//    test.RunTests();
//    }
//
//    {
//    OtusAlgo::BitFEN fen;
//    OtusAlgo::Tester test(fen, this_file.parent_path().string() + "/tests/fen");
//    test.RunTests();
//    }
//
    {
    OtusAlgo::BitStrickers fen;
    OtusAlgo::Tester test(fen, this_file.parent_path().string() + "/tests/strickers");
    test.RunTests();
    }

    
    return 0;
}
