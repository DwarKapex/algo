#include <Tester.h>
#include <filesystem>
#include <fstream>

namespace OtusAlgo {

namespace fs = std::filesystem;

Tester::Tester(ITask& task, std::string path):
        m_task(task), m_path(std::move(path)) {}
    
void Tester::UpdateTask(ITask& new_task) {
    m_task = new_task;
}

std::vector<size_t> Tester::RunTests(const size_t n, std::ostream& out) {
    std::vector<size_t> times;
    size_t test_nr = 0;
    while (test_nr <= n) {
        std::string common_prefix = m_path + "/test." + std::to_string(test_nr);

        std::string inFile  = common_prefix + ".in",
                   outFile  = common_prefix + ".out";
        
        if (!fs::exists(inFile) || !fs::exists(outFile))
            break;
        auto start = std::chrono::system_clock::now();
        bool result = RunTest(inFile, outFile);
        auto end = std::chrono::system_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
        times.push_back(us);
        out << "Test # " << test_nr << " - " << std::boolalpha << result << std::endl;
        ++test_nr;
    }
    return times;
}

bool Tester::RunTest(std::string in_file, std::string out_file) {
    ITask::DataType data;
    std::ifstream inFile (in_file.c_str()),
                  outFile (out_file.c_str());
    std::string input;
    if (inFile.is_open()) {
        while(inFile >> input) {
            data.push_back(input);
        }
        inFile.close();
    }
    
    std::string expected, exp;
    if (outFile.is_open()) {
        while(outFile >> exp) {
            expected += exp + ' ';
        }
        outFile.close();
    }
    
    std::string actual = m_task.Run(data);
    return expected == actual;
    
}
}

