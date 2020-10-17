#include <iostream>
#include <string>
#include <queue>
#include <memory>

using namespace std;

using Map = vector<vector<int>>;

void find_island(Map& m, int x, int y){
    queue<pair<int,int>> q;
    q.push({x,y});
    while (!q.empty()) {
        auto [x,y] = q.front();
        //int x = b.first, y = b.second;
        m[x][y] = 0;
        q.pop();
        if (m[x-1][y] == 1) q.push({x-1,y});
        if (m[x+1][y] == 1) q.push({x+1,y});
        if (m[x][y-1] == 1) q.push({x,y-1});
        if (m[x][y+1] == 1) q.push({x,y+1});
    }
}

int main()
{
    int n = 0;
    cin >> n;
    Map map(n+2, vector<int>(n+2,0));
    for (int I = 1; I <=n ; ++I)
        for (int j = 1; j <= n; ++j) {
            int a = 0;
            cin >> a;
            map[I][j] = a;
        }
    int idx = 0, count = 0;
    while (idx < n*n){
        if (map[idx/n+1][idx%n+1]) {
            find_island(map, idx/n,idx%n);
            ++count;
        }
    }
    cout << count << endl;
    return 0;
}