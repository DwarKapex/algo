#include "RLE.h"

namespace OtusAlgo {

std::vector<char> RLECompress(const std::vector<char>& input, bool improved) {
    if (input.empty()) {
        return {};
    }
    uint8_t limitPositive = 128;
    char last_char = input[0];
    std::vector<char> result;
    result.reserve(input.size()*2);
    if (!improved) {
        uint8_t count = 0;
        for (const char c: input) {
            if (c == last_char) {
                ++count;
                if (count == limitPositive) {
                    result.push_back(count);
                    result.push_back(last_char);
                    count = 0;
                }
            }
            else {
                result.push_back(count);
                result.push_back(last_char);
                last_char = c;
                count = 1;
            }
        }
        if (count > 0) {
            result.push_back(count);
            result.push_back(last_char);
        }
    }
    else {
        int8_t count = 0, single_count = 0;
        int limitNegative = 127;
        for (size_t i = 0; i < input.size(); ++i) {
            if (input[i] == last_char) {
                if (single_count > 1) {
                    result.push_back(-single_count);
                    for (size_t j = 0; j < single_count; ++j){
                        result.push_back(input[i-single_count+j]);
                    }
                    single_count=0;
                }
                ++count;
                single_count = 0;
                if (count == limitPositive) {
                    result.push_back(count);
                    result.push_back(last_char);
                    count = 0;
                }
            }
            else {
                if (count > 1) {
                    result.push_back(count);
                    result.push_back(last_char);
                }
                ++single_count;
                count = 1;
                if (single_count == limitNegative) {
                    result.push_back(-limitNegative);
                    for (size_t j = 0; j < single_count; ++j){
                        result.push_back(input[i-single_count+j]);
                    }
                    single_count=0;
                }
                last_char = input[i];
            }

        }
        if (count > 1) {
            result.push_back(count);
            result.push_back(last_char);
        }
        if (single_count > 1) {
            result.push_back(-single_count);
            for (size_t j = 0; j < single_count; ++j){
                result.push_back(input[input.size()-single_count+j]);
            }
        }

    }
    result.shrink_to_fit();
    return result;
}

std::vector<char> RLEDecompress(const std::vector<char>& input, bool improved) {
    std::vector<char> result;
    if (!improved) {
        if (input.size() % 2) {
            throw std::runtime_error("Something wrong with data. Size of data should be even");
        }
        for (size_t i = 0; i < input.size(); i+=2) {
            for (int count = 0; count < static_cast<int>(input[i]); ++count) {
                result.push_back(input[i+1]);
            }
        }
    }
    else {
        size_t i = 0;
        while (i < input.size()) {
            int n = static_cast<int>(input[i]);
            size_t increment = 0;
            if (n < 0) increment = 1;
            for (int j = 0; j < std::abs(n); ++j, i+=increment) {
                result.push_back(input[i+1]);
            }
            if (n < 0) i+=std::abs(n);
            else i+=2;
        }
    }
    return result;
}

} // namespace OtusAlgo
