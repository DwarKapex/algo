#include "String.h"

namespace OtusAlgo {

std::string String::Run(const ITask::DataType& data) {
    if (!data.empty()) {
        return std::to_string(data.front().length());
    }
    else {
        return "0";
    }
}

} //namespace OtusAlgo
