#include <iostream>
#include <stdlib.h>
#include <stdbool.h>

using namespace std;

int main(){
    int len;
    cin >> len;
    long long *prices = new long long[len];
    for (int i = 0; i < len; i++){
        cin >> prices[i];
    }
    int days;
    cin >> days;
    int *products = new int[days];
    for (int i = 0; i < days; i++){
        cin >> products[i];
    }

    for (int j = 0; j < days; j++){
        long long solution = 0;
        int indexLastEven = -1;
        int indexLastOdd = -1;
        if (products[j] > len){
            solution = -1;
        }else{
            for (int i = len - 1; i >= len - products[j]; i--){
                solution += prices[i];
                if (prices[i] % 2 == 0){
                    indexLastEven = i;
                }else{
                    indexLastOdd = i;
                }
            }
            if (solution % 2 == 0){
                long long solutionCrossingEven = solution;
                long long solutionCrossingOdd = solution;
                int k = len - products[j] - 1;
                bool validCrossingEven = false;
                bool validCrossingOdd = false;
                
                if (indexLastEven >= 0){
                    solutionCrossingEven -= prices[indexLastEven];
                    while (k >= 0 && (prices[k] % 2 == 0)){
                        k--;
                    }
                    if (k >= 0){
                        solutionCrossingEven += prices[k];
                        validCrossingEven = true;
                    }else{
                        validCrossingEven = false;
                    }
                }
                
                k = len - products[j] - 1;
                if (indexLastOdd >= 0){
                    solutionCrossingOdd -= prices[indexLastOdd];
                    while (k >= 0 && (prices[k] % 2 == 1)){
                        k--;
                    }
                    if (k >= 0){
                        solutionCrossingOdd += prices[k];
                        validCrossingOdd = true;
                    }else{
                        validCrossingOdd = false;
                    }
                }
                if (validCrossingOdd && validCrossingEven){
                    if (solutionCrossingOdd >= solutionCrossingEven){
                        solution = solutionCrossingOdd;
                    }else{
                        solution = solutionCrossingEven;
                    }
                }else if (validCrossingOdd){
                    solution = solutionCrossingOdd;
                }else if (validCrossingEven){
                    solution = solutionCrossingEven;
                }else{
                    solution = -1;
                }
            }
        }
        cout << solution << endl;
    }

    delete [] products;
    delete [] prices;
    return 0;
}