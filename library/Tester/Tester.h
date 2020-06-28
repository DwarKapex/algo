#pragma once

#include <ITask.h>
#include <iostream>
#include <limits>
#include <chrono>
#include <ctime>
#include <vector>

namespace OtusAlgo {

class Tester {
public:
    Tester(ITask& task, std::string path);
    void UpdateTask(ITask& new_task);
    std::vector<size_t> RunTests(const size_t n = std::numeric_limits<size_t>::max(), std::ostream& out = std::cout);
    
    bool RunTest(std::string inFile, std::string outFile);

private:
        
    ITask& m_task;
    std::string m_path;
};

}
