#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    string result = "TAK";
    int n;
    int m;
    cin >> n;
    cin >> m;
    int x;

    unsigned long long* zawodnicy = new unsigned long long[n];
    for (int i = 0; i < n; i++){
        zawodnicy[i] = 0;
    }

    for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> x;
            if (j < n/2){
                zawodnicy[x - 1] += 1;
            }
        }
        for(int j = 0; j < n; j++){
            zawodnicy[j] = zawodnicy[j] * 2;
        }
    }

    sort(zawodnicy, zawodnicy + n);
    
    for (int i = 0; i < n - 1; i++){
        if (zawodnicy[i] == zawodnicy[i + 1]){
            result = "NIE";
        }
    }

    cout << result;

    delete [] zawodnicy;

    return 0;
}

/*
Czy dla każdego (i,j) i zagra przeciwko j?
ZE WSKAZÓWKI: Czy istnieje (i,j), że i zawsze z j w tej samej drużynie
Dla każdego zawodnika w preproccessingu: każdy zawdonik ma kolumne 0/1
Czyli 4 6 1 3 5 2 byłoby 0 1 1 0 1 0
i teraz kolumna to jest liczba dwójkowa
dla każdego zawodnika robimy z tego liczbę dziesiętną
czyli tablica z jednym wierszem
potem sortujemy tablicę 
sprawdzamy czy są dwie takie same liczby
#include <algorithm>
sort(z, z+n) dla tablicy z, bo z to wskaźnik

jak tworzyć z liczby bitowej liczbe dziesiętną?
coe jeśli w tablicy od najstarszych?
przechodzimy przez pierwszym mecz
wpisujemy 0/1
przemnażamy przez 2
itd
dodajemy 0/1
przemnażamy przez 2

jeśli w tablicy od najmłodzych
to dodajemy 0/1
0/2
0/4 etc

z pomocą tricków bitowych
j to zawodnik, i to numer meczu
z[j] = z[j] | (1  << i - 1)

strona cppreference.com
if (s.find(x) != s.end())

6 3
4 6 1 3 5 2
1 4 5 2 3 6
1 2 6 4 5 3
*/
