#include "String.h"
#include <Tester.h>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
int main() {
    OtusAlgo::String str;
    std::filesystem::path this_file = __FILE__;
    OtusAlgo::Tester test(str, this_file.parent_path().string() + "/tests");
    test.RunTests();
            
    return 0;
}
