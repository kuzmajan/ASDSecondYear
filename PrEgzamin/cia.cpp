//
// Created by kuzma on 02.02.2024.
//
#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    priority_queue<int> len;
    priority_queue<int> del;
    int n, m, low;
    cin >> n >> m;
    len.push(n);
    set<int> nums;
    nums.insert(n);
    nums.insert(0);
    for (int i = 0; i < m; i++){
        cin >> low;
        auto temp = nums.lower_bound(low);
        if (!(*temp == low)){
            int first = *temp;
            temp--;
            int second = *temp;
            nums.insert(low);
            len.push(first - low);
            len.push(low - second);
            del.push(first - second);
            while (!del.empty() && del.top() == len.top()){
                del.pop();
                len.pop();
            }
        }
        cout << len.top() << "\n";
    }

    return 0;
}
