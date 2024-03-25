//
// Created by kuzma on 01.02.2024.
//
#include <iostream>
#include <vector>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    long x;
    long *input = new long[n];
    for (int i = 0; i < n; i++){
        std::cin >> x;
        input[i] = x;
    }
    int i = 1;
    long long licznik = 0;
    long *dpP = new long[n];
    long *dpNP = new long[n];
    while(i < n){
        dpP[0] = (input[i - 1] + 1)% 2;
        dpNP[0] = input[i - 1] % 2;
        int j = 0;
        if (input[i] > input[i - 1]){
            while (input[i] > input[i - 1] && i < n){
                if(input[i] % 2 == 0){
                    licznik += dpP[j];
                }else{
                    licznik += dpNP[j];
                }
                j++;
                if(input[i] % 2 == 0){
                    dpP[j] = dpP[j - 1] + 1;
                    dpNP[j] = dpNP[j - 1];
                }else{
                    dpP[j] = dpNP[j - 1];
                    dpNP[j] = dpP[j - 1] + 1;
                }
                i++;
            }
        }else if(input[i] < input[i - 1]){
            while (input[i] < input[i - 1] && i < n){
                if(input[i] % 2 == 0){
                    licznik += dpP[j];
                }else{
                    licznik += dpNP[j];
                }
                j++;
                if(input[i] % 2 == 0){
                    dpP[j] = dpP[j - 1] + 1;
                    dpNP[j] = dpNP[j - 1];
                }else{
                    dpP[j] = dpNP[j - 1];
                    dpNP[j] = dpP[j - 1] + 1;
                }
                i++;
            }
        }else{
            while (input[i] == input[i - 1] && i < n){
                if(input[i] % 2 == 0){
                    licznik += dpP[j];
                }else{
                    licznik += dpNP[j];
                }
                j++;
                if(input[i] % 2 == 0){
                    dpP[j] = dpP[j - 1] + 1;
                    dpNP[j] = dpNP[j - 1];
                }else{
                    dpP[j] = dpNP[j - 1];
                    dpNP[j] = dpP[j - 1] + 1;
                }
                i++;
            }
        }
    }
    std::cout << licznik;


    delete [] dpP;
    delete [] dpNP;
    delete [] input;
    return 0;
}