#include <iostream>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;


int main(){
    int len;
    cin >> len;
    int *s = new int[len];
    for(int i = 0; i < len; i++){
        cin >> s[i];
    }

    int** dp = new int*[len];
    int** L = new int*[len];
    int** R = new int*[len];
    for(int i = 0; i < len; ++i){
        dp[i] = new int[len];
        L[i] = new int[len];
        R[i] = new int[len];
    }
    
    int m = 1000000000;

    if (len == 1){
        cout << "1" << endl; 
    } else {
        for (int d = 2; d <= len; d++){
            for(int i = 0; i + d <= len; i++){
                int j = d + i - 1;
                if (i == j - 1){
                    L[i][j] = (s[i] < s[i + 1]);
                    R[i][j] = (s[i] < s[i + 1]);
                }else if (i < j){
                    L[i][j] = ((s[i] < s[i + 1]) * L[i + 1][j] + (s[i] < s[j]) * R[i + 1][j]) % m;
                    R[i][j] = ((s[j] > s[i]) * L[i][j - 1] + (s[j] > s[j - 1]) * R[i][j - 1]) % m;
                }
            }
        }
        cout << (L[0][len - 1] + R[0][len - 1]) % m;
    }

    for(int i = 0; i < len; ++i) {
        delete [] dp[i];
        delete [] R[i];
        delete [] L[i];
    }
    delete [] dp;
    delete [] R;
    delete [] L;
    delete[] s;

    return 0;
}