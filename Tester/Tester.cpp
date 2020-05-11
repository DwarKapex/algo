#include <Tester.h>
#include <filesystem>
#include <fstream>

namespace OtusAlgo {

namespace fs = std::filesystem;

Tester::Tester(ITask& task, std::string path):
        m_task(task), m_path(std::move(path)) {}
    
void Tester::RunTests(const size_t n, std::ostream& out) {
    size_t test_nr = 0;
    while (test_nr <= n) {
        std::string common_prefix = m_path + "/test." + std::to_string(test_nr);

        std::string inFile  = common_prefix + ".in",
                   outFile  = common_prefix + ".out";
        
        if (!fs::exists(inFile) || !fs::exists(outFile))
            break;
        out << "Test # " << test_nr << " - " << std::boolalpha << RunTest(inFile, outFile) << std::endl;
        ++test_nr;
    }
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
            expected+=exp;
        }
        outFile.close();
    }
    
    std::string actual = m_task.Run(data);
    return expected == actual;
    
}
}

