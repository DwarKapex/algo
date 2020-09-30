#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include "RLE.h"
#include <FileIO.h>
#include <vector>
#include <filesystem>
#include <limits>

namespace po = boost::program_options;


int main(int argc, char* argv[]) {
    std::string input_file, output_file;
    bool improved = false, compress = false, decompress = false;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("input_file,i", po::value<std::string>(&input_file), "set input file")
        ("output_file,o", po::value<std::string>(&output_file), "set output file")
        ("use_improved,u", po::bool_switch(&improved)->default_value(true), "use improved algo")
        ("compress,c", po::bool_switch(&compress)->default_value(true), "compress?")
        ("decompress,d", po::bool_switch(&decompress)->default_value(false), "decompress?")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (input_file.empty()) {
        std::cout << "Input file is not set. Nothing to compress\n";
        return -1;
    }

    if (output_file.empty()) {
        std::cout << "Output file is not set. Save output to /dev/null\n";
    }

    if (compress && decompress){
        std::cout << "You cannot set both compression and decompression at the same time\n";
        return -2;
    }

    std::vector<char> result;
    auto data = OtusAlgo::ReadBinaryFile(std::filesystem::path(input_file));

    if (compress){
        result = OtusAlgo::RLECompress(data, improved);
    }
    else if (decompress) {
        result = OtusAlgo::RLEDecompress(data, improved);
    }
    else {
        std::cout << "Tell me next time what to do: compress or decompress\n";
    }

    OtusAlgo::WriteBinaryFile(std::filesystem::path(output_file), result);
    
//    std::vector<char> a{1,1,2,2,3,4,5,6,7};
//    // improved algo
//    auto res = OtusAlgo::RLECompress(a);
//    auto deres = OtusAlgo::RLEDecompress(res);
//    assert(a == deres);
//
//    // Not improved algo
//    auto res1 = OtusAlgo::RLECompress(a, false);
//    auto deres1 = OtusAlgo::RLEDecompress(res1, false);
//    assert(a == deres1);
//
//    assert(res1.size() >= res.size());
    return 0;
}
