#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    std::vector<int> tree(n*(n+1)/2,0);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j< i+1; ++j) {
            int a;
            cin >> a;
            tree[i*(i+1)/2+j] = a;
        }
    }
    for (int level = 2; level <= n; ++level) { 
        int left = (level-2)*(level-1)/2;      
        int right = left+level-1;              
        for (int shift = 0; shift < level; ++shift) {
            int idx = right + shift;          
            if (idx - level < left) {         
                tree[idx] += tree[idx - level+1];
            }
            else if (idx - level+1 >= right) {
                tree[idx] += tree[idx - level];
            }
            else {
                tree[idx] += std::max(tree[idx - level], tree[idx - level+1]);
            }
        }
    }
    auto s = tree.begin();
    std::advance(s, tree.size()/2);
    std::cout << *std::max_element(s, tree.end()) << std::endl;
}