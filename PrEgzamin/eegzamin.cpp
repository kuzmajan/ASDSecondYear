#include <iostream>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int len;
    std::cin >> len;
    long *akcje = new long[len];
    for(int i = 0; i < len; i++){
        std::cin >> akcje[i];
    }
    int i = 0;
    long long result = 0;
    long akt = 0;
    while(i < len - 1){
        if(akcje[i] < akcje[i + 1]){
            if(akt == 0){
                akt = akcje[i];
            }
            if(i == len - 2){
                result += (akcje[i + 1] - akt);
            }
        }else{
            if (akt > 0){
                result += (akcje[i] - akt);
                akt = 0;
            }
        }
        i++;
    }
    std::cout << result;

    delete[] akcje;

    return 0;
}