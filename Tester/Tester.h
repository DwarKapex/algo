#pragma once

#include <ITask.h>
#include <iostream>
#include <limits>

namespace OtusAlgo {

class Tester {
public:
    Tester(ITask& task, std::string path);
    
    void RunTests(const size_t n = std::numeric_limits<size_t>::max(), std::ostream& out = std::cout);
    
    bool RunTest(std::string inFile, std::string outFile);

private:
        
    ITask& m_task;
    std::string m_path;
};

}
