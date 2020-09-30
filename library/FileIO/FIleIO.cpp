#include <FileIO.h>
#include <memory>

namespace OtusAlgo {


bool CompareBinaryFiles(std::filesystem::path lhs, std::filesystem::path rhs) {
    std::ifstream lFile(lhs.string(), std::ios::in | std::ios::binary);
    std::ifstream rFile(rhs.string(), std::ios::in | std::ios::binary);
    
    constexpr size_t BufferSize = 1 << 20; // 1 mb
    
    // fail to open one of the files
    if (lFile.fail() || rFile.fail()) {
      return false;
    }

    //size mismatch
    if (lFile.tellg() != rFile.tellg()) {
      return false;
    }

    // because it's faster
    std::unique_ptr<char> lBuffer(new char[BufferSize]);
    std::unique_ptr<char> rBuffer(new char[BufferSize]);

    do {
        lFile.read(lBuffer.get(), BufferSize);
        rFile.read(rBuffer.get(), BufferSize);

        if (std::memcmp(lBuffer.get(), rBuffer.get(), BufferSize) != 0)
        {
            return false;
        }
    } while (lFile.good() || rFile.good());

    return true;
        
//    //seek back to beginning and use std::equal to compare contents
//    lFile.seekg(0, std::ifstream::beg);
//    rFile.seekg(0, std::ifstream::beg);
//    return std::equal(std::istreambuf_iterator<char>(lFile.rdbuf()),
//                    std::istreambuf_iterator<char>(),
//                    std::istreambuf_iterator<char>(rFile.rdbuf()));
}



}

