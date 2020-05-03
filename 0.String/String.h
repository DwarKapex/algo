#pragma once

#include <ITask.h>

namespace OtusAlgo {

class String: public ITask {
public:
    
    std::string Run(const ITask::DataType&) override;
};

} //namespace OtusAlgo

