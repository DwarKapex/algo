#pragma once

#include <string>
#include <vector>

namespace OtusAlgo {

class ITask {
public:
    using DataType = std::vector<std::string>;
    virtual std::string Run(const DataType& data) = 0;
};

}
