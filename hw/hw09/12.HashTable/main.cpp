#include <fstream>
#include <cmath>
#include <vector>
#include <cstdint>

int N  = 0;

void updateTree(std::vector<long>& tree, int i, int x) {
    i += N - 1;
    tree[i] = x;
    do {
        i /= 2;
        tree[i] = tree[2*i] + tree[2*i + 1];
    } while (i > 1);
    
}


long getSum(const std::vector<long>& tree, int L, int R) {
    long sum = 0;
    L += N - 1;
    R += N - 1;
    while (L <= R) {
        if (L % 2 != 0) sum += tree[L];
        if (R % 2 == 0) sum += tree[R];
        L = (L+1) / 2;
        R = (R-1) / 2;
    }
    return sum;
}


int main() {
    std::ifstream input("sum.in", std::ios::in);
    std::ofstream output("sum.out", std::ios::out);
    if (!input.is_open())
        throw std::runtime_error("Cannot open file sum.in");
    
    int K = 0, pos = 0, value = 0;
    input >> N >> K;
    size_t p = std::ceil(log2(N));
    N = 1 << p;
    std::vector<long> tree (2*N, 0);
    char req;
    for (int i = 0; i < K; ++i) {
        input >> req >> pos >> value;
        switch(req) {
            case 'A':
                updateTree(tree, pos, value);
                break;
            case 'Q':
                output << getSum(tree, pos, value) << std::endl;
                break;
        }
    }
    input.close();
    output.close();
    
    return 0;
}
