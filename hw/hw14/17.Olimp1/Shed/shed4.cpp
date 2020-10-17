#include <iostream>
#include <vector>
#include <stack>

using Map = std::vector<std::vector<int>>;

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

void GetHeightD(const Map& m, int y, std::vector<int>& line)
{
    const int N = m.size();
    for (size_t x = 0; x < N; ++x) {
        if (m[x][y] == 0)
            ++line[x];
        else
            line[x] = 0;
    }
}

int Shed4(const Map &m)
{
    if (m.empty()) {
        return 0;
    }
    
    const size_t M = m[0].size();
    const size_t N = m.size();
    int maxSquare = -1;
    std::vector<int> line(N);
    std::vector<int> L(N), R(N);

    for (int y = 0; y < M; ++y)
    {
        GetHeightD(m, y, line);
        Shed3(line, L, R);

        for (size_t x = 0; x < N; ++x) {
            int square = (R[x]-L[x]+1)*line[x];
            if (square > maxSquare)
                maxSquare = square;
        }
    }
    
    return maxSquare;
}

int main() {
    size_t n,m;
    std::cin >> n >> m;
    Map field(n, std::vector<int>(m,0));
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        field[x][y] = 1;
    }

    std::cout << Shed4(field) << std::endl;

    return 0;
}
