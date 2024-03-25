/*
da każdego j: 1...k istnieje inwersja która się kończy na tym elemencie
dp[i][j] - liczba j inwersji kończących się na ai, czyli np dp[2][3] to liczba 3-inwersji kończących się na a2
dp[i][j] = suma (l < i, a_l > a_i) dp[l][j-1]
n * k       * n (suma liniowo) - za pomocą drzewa przedziałowego zejdziemy do czasu logarytmicznego
*/


#include <iostream>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;

int main(){
    int n;
    int k;
    cin >> n;
    cin >> k;
    int *p = new int[n];
    for(int i = 0; i < n; i++){
        cin >> p[i];
    }

    int** dp = new int*[n];
    for(int i = 0; i < n; ++i){
        dp[i] = new int[k];
    }
    
    int m = 1000000000;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            if(j == 0){
                dp[i][j] = 1;
            }else{
                int suma = 0;
                for(int l = 0; l < i; l++){
                    if(p[l] > p[i]){
                        suma = (suma + dp[l][j - 1]) % m;
                    }
                }
                dp[i][j] = suma;
            }
        }
    }

    int result = 0;

    for(int i = 0; i < n; i++){
        result = (result + dp[i][k - 1]) % m;
    }

    cout << result;

    for(int i = 0; i < n; ++i) {
        delete [] dp[i];
    }
    delete [] dp;
    delete[] p;

    return 0;
}