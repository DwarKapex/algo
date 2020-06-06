#include "Tickets.h"

namespace OtusAlgo {

std::string Tickets::Run(const ITask::DataType& data) {
    if (data.empty()) {
        return "0";
    }
    int n = std::stoi(data.front());
    std::vector<uint64_t> sums(10*n,0);
    Calculate(sums, n, 0);
    uint64_t total = 0;
    for (uint64_t item: sums) {
        total += item*item;
    }
    return std::to_string(total);
}

void Tickets::Calculate(std::vector<uint64_t>& sums, int idx, int sum) {
    if (idx == 0) {
        ++sums[sum];
        return;
    }
    for (int i = 0; i < 10; ++i) {
        Calculate(sums, idx-1, sum + i);
    }
}

} //namespace OtusAlgo
