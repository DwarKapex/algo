#pragma once

#include <ITask.h>

namespace OtusAlgo {

class Tickets: public ITask {
public:
    
    std::string Run(const ITask::DataType&) override;
    
    void Calculate(std::vector<uint64_t>& sums, int idx, int sum);
};

} //namespace OtusAlgo

