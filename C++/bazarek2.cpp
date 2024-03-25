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
    
    long long* leftMaxEven = new long long[len];
    long long* leftMaxOdd = new long long[len];
    long long* sum = new long long[len];
    long long* rightMinEven = new long long[len];
    long long* rightMinOdd = new long long[len];

    leftMaxEven[0] = -1;
    leftMaxOdd[0] = -1;
    for (int i = 1; i < len; i++){
        if(prices[i - 1] % 2 == 0){
            leftMaxEven[i] = prices[i - 1];
            leftMaxOdd[i] = leftMaxOdd[i - 1];
        }else{
            leftMaxOdd[i] = prices[i - 1];
            leftMaxEven[i] = leftMaxEven[i - 1];
        }
    }

    sum[len - 1] = prices[len - 1];
    if((prices[len - 1] % 2) == 0){
        rightMinEven[len - 1] = prices[len - 1];
        rightMinOdd[len - 1] = -1;
    }else{
        rightMinOdd[len - 1] = prices[len - 1];
        rightMinEven[len - 1] = -1;
    }
    for (int i = len - 2; i >= 0; i--){
        sum[i] = sum[i + 1] + prices[i];
        if(prices[i] % 2 == 0){
            rightMinEven[i] = prices[i];
            rightMinOdd[i] = rightMinOdd[i + 1];
        }else{
            rightMinOdd[i] = prices[i];
            rightMinEven[i] = rightMinEven[i + 1];
        }
    }

    for(int j = 0; j < days; j++){
        long long solution = 0;
        if(products[j] > len){
            solution = -1;
        }else{
            int k = len - products[j];
            if(sum[k] % 2 == 1){
                solution = sum[k];
            }else{
                long long solutionEven = sum[k];
                long long solutionOdd = sum[k];
                bool evenValid = ((rightMinEven[k] != -1) && (leftMaxOdd[k] != -1));
                bool oddValid = ((rightMinOdd[k] != -1) && (leftMaxEven[k] != -1));
                if (evenValid){
                    solutionEven -= rightMinEven[k];
                    solutionEven += leftMaxOdd[k];
                }
                if(oddValid){
                    solutionOdd -= rightMinOdd[k];
                    solutionOdd += leftMaxEven[k];
                }

                if(oddValid && evenValid){
                    if(solutionEven >= solutionOdd){
                        solution = solutionEven;
                    }else{
                        solution = solutionOdd;
                    }
                }else if(oddValid){
                    solution = solutionOdd;
                }else if(evenValid){
                    solution = solutionEven;
                }else{
                    solution = -1;
                }
            }
        }  
        cout << solution << endl;
    }

    delete [] leftMaxEven;
    delete [] leftMaxOdd;
    delete [] sum;
    delete [] rightMinEven;
    delete [] rightMinOdd;
    delete [] products;
    delete [] prices;
    return 0;
}