#include <iostream>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;

int main(){
    int n;
    int k;
    cin >> n;
    cin >> k;
    int *input = new int[n];
    int *result = new int[n];
    int *prev = new int[k + 1];
    int *next = new int[k + 1];
    
    for(int i = 0; i < n; i++){
        cin >> input[i];
    }

    int m = 1000000000;

    for (int i = 0; i < k + 1; i++){
        prev[i] = 1;
    }
    result[0] = k + 1;

    for (int i = 1; i < n; i++){
        result[i] = 0;
        for (int j = 1; j < k; j++){
            next[j] = (prev[j - 1] + prev[j]) % m;
            next[j] = (next[j] + prev[j + 1]) % m;
            result[i] = (result[i] + next[j]) % m;
        }
        next[0] = (prev[0] + prev[1]) % m;
        next[k] = (prev[k - 1] + prev[k]) % m;
        result[i] = (result[i] + next[0]) % m;
        result[i] = (result[i] + next[k]) % m;
        for (int j = 0; j < k + 1; j++){
            prev[j] = next[j];
        }        
    }

    for(int i = 0; i < n; i++){
        cout << result[input[i] - 1] << " "; 
    }
        
    delete [] input;
    delete [] result;
    delete [] prev;
    delete [] next;

    return 0;
}