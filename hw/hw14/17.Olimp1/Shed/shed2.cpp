#include <iostream>
#include <vector>

using namespace std;
using Field = vector<vector<size_t>>;


void GetHeightD(const Field& m, int y, vector<size_t>& line)
{
    const int N = m.size();
    for (size_t x = 0; x < N; ++x) {
        if (m[x][y] == 0)
            ++line[x];
        else
            line[x] = 0;
    }
}

Field Shed2(const Field& m)
{
    if (m.empty()){
        return {};
    }
    const int M = m[0].size();
    const int N = m.size();
    Field result;
    vector<size_t> line(N);

    for (int y = 0; y < M; ++y)
    {
        GetHeightD(m, y, line);
        result.push_back(line);
    }

    return result;
}
