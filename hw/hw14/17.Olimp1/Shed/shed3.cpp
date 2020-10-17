#include <iostream>
#include <vector>
#include <stack>

void Shed3(const std::vector<int> &field, std::vector<int> &L, std::vector<int> &R)
{
    const size_t N = field.size();

    std::stack<int> s;
    for (size_t i = N-1; i >= 0; --i) {
        while (!s.empty() && (field[i] < field[s.top()])) {
                L[s.top()] = i+1;
                s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        L[s.top()] = 0;
        s.pop();
    }

    for (size_t i = 0; i < N; ++i) {
        while (!s.empty() && (field[i] < field[s.top()])) {
                R[s.top()] = i-1;
                s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        R[s.top()] = N-1;
        s.pop();
    }
}

int main() {
    int n, t;
    std::cin >> n;
    std::vector<int> field(n,0);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> t;
        field[i] = t;
    }
    std::vector<int> L(n, 0), R(n, 0);
    Shed3(field, L, R);
    for (size_t i = 0; i < n; ++i)
        std::cout << L[i] << ((i == n-1) ? "\n" : " ");
    for (size_t i = 0; i < n; ++i)
        std::cout << R[i] << ((i == n-1) ? "\n": " ");

    return 0;
}
