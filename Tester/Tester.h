#pragma once

#include <ITask.h>
#include <iostream>

namespace OtusAlgo {

class Tester {
public:
    Tester(ITask& task, std::string path);
    
    void RunTests(std::ostream& out = std::cout);
    
    bool RunTest(std::string inFile, std::string outFile);

private:
        
    ITask& m_task;
    std::string m_path;
};

}
