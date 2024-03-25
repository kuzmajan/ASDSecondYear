#include <iostream>
#include <stdlib.h>
#include <algorithm>

/*
n - k + 1 = d + 1
k = n - d
*/

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string wallpaper;
    cin >> wallpaper;
    char latestLetter = wallpaper[0];
    int actualLength = 0;
    int minStarsBetween = wallpaper.length() - 1;
    bool minInitialized = false;
    for (int i = 1; i < wallpaper.length(); i++){
        if (wallpaper[i] != '*'){
            if(latestLetter != wallpaper[i]){
                if(!minInitialized){
                    minInitialized = true;
                    if(latestLetter != '*'){
                        minStarsBetween = actualLength;
                    }
                }else{
                    minStarsBetween = min(minStarsBetween, actualLength);
                }
            }
            latestLetter = wallpaper[i];
            actualLength = 0;            
        }else{
            actualLength++;
        }
    }
    cout << wallpaper.length() - minStarsBetween << endl;
    return 0;
}