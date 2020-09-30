#pragma once

#include <vector>
namespace OtusAlgo {

std::vector<char> RLECompress(const std::vector<char>&, bool improved = true);
std::vector<char> RLEDecompress(const std::vector<char>&, bool improved = true);

} // namespace OtusAlgo


