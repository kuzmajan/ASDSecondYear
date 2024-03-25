//
// Created by kuzma on 02.02.2024.
//
#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long num[11];
    for (int i = 1; i < 11; i++){
        num[i] = 0;
    }
    long long score = 0;
    int n, got;
    cin >> n;
    cin >> got;
    num[got]++;
    cin >> got;
    num[got]++;

    for (int i = 0; i < n - 2; i++){
        cin >> got;
        if (got == 2){
            score += num[1] * (num[1] - 1) / 2;
        }
        else if (got == 3){
            score += num[2] * num[1];
        }
        else if (got == 4){
            score += num[3] * num[1];
            score += num[2] * (num[2] - 1) / 2;
        }
        else if (got == 5){
            score += num[4] * num[1];
            score += num[3] * num[2];
        }
        else if (got == 6){
            score += num[5] * num[1];
            score += num[4] * num[2];
            score += num[3] * (num[3]-1) / 2;
        }
        else if (got == 7){
            score += num[6] * num[1];
            score += num[5] * num[2];
            score += num[4] * num[3];
        }
        else if (got == 8){
            score += num[7] * num[1];
            score += num[6] * num[2];
            score += num[5] * num[3];
            score += num[4] * (num[4] - 1) / 2;
        }
        else if (got == 9){
            score += num[8] * num[1];
            score += num[7] * num[2];
            score += num[6] * num[3];
            score += num[5] * num[4];
        }
        else if (got == 10){
            score += num[9] * num[1];
            score += num[8] * num[2];
            score += num[7] * num[3];
            score += num[6] * num[4];
            score += num[5] * (num[5] - 1) / 2;
        }
        num[got]++;
    }
    cout << score;
    return 0;
}