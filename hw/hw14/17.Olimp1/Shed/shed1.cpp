#include <iostream>
#include <vector>

using namespace std;

//---------------------------------------------------------------
#pragma mark - Shed Ver1
//---------------------------------------------------------------

int GetHeight(const vector<vector<int>> &m, int x, int y)
{
    const int M = m[0].size();
    int yh = y;
    while (yh < M && m[x][yh] == 0)
        yh++;
    return yh - y;
}

int CalcMaxSquare(const vector<vector<int>> &m, int x, int y)
{
    int minHeight = GetHeight(m, x, y);
    if (!minHeight)
        return 0;

    const int N = m.size();
    int maxSquare = minHeight;
    for (int xw = x+1; xw < N; ++xw)
    {
        int height = GetHeight(m, xw, y);
        if (!height)
            return maxSquare;
        if (minHeight > height)
            minHeight = height;
        int square = (xw-x+1)*minHeight;
        if (square > maxSquare)
            maxSquare = square;
    }
    return maxSquare;
}

unsigned Shed1(const vector<vector<int>> &m)
{
    if (m.empty())
        return 0;
    const int M = m[0].size();
    const int N = m.size();
    int maxSquare = -1;
    for (int y = 0; y < M; ++y)
        for (int x = 0; x < N; ++x)
        {
            int square = CalcMaxSquare(m, x, y);
            if (square > maxSquare)
                maxSquare = square;
        }

    return maxSquare;
}

int main() {
    size_t n,m;
    cin >> n >> m;
    vector<vector<int>> field(n, vector<int>(m,0));
    int cell;
    for (size_t y = 0; y < m; ++y)
        for (size_t x = 0; x < n; ++x)
        {
            cin >> cell;
            field[x][y] = cell;
        }

    cout << Shed1(field) << endl;
    
    return 0;
}
