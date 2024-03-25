
/*
A teraz drzewo przedziałowe nklogn
pozioma oś dyskretna od 1 do n
zadajemy pytania o przedziały których końce to jakieś liczby całkowite

Najprostsze zastosowanie:
a1 ... an to 0/1
*zapytania postaci dla 1 <= i <= j <= n podaj suma (l od i do j) a_l
*operacje- zmiana ai
-> obie operacje w czasie log, zatem struktura to pene drzewo binarne o 2n > B >= n liściach


w liściach wpisany ciąg a1 ... an
każdy węzeł- suma wartości w liściach
góra dół:
jeżeli cały przedział się mieści -> dodajemy wartość z węzła syna, inaczej- schodzimy w dół

z dołu do góry:
najniższy wspólny przodek
na lewej ścieżce jeśli przyszliśmy z lewej, to sumujemy prawe

aktualizacja:
zmieniamy liść, aktualizujemy w góre, zatem liść zmieniamy, węzęł aktualizujemy że to suma synów

Reprezentacja trochę jak w kopcu, t[1, 2B-1]- pełne drzewo binarne, korzeń w t[1], synowie t[i] są w t[2i] oraz t[2i + 1] jeśli idziemy w dół
jeśli idzimy do góry: ojciec t[i]  w t[i/2]
czy lewy czy prawy syn to parzystość indeksu syna

dopóki indeksy się nie spotkają dodaejmy i idziemy piętro wyżej

Jak to sie ma do zadania?

Możemy lcizyć sumę w czasie logarytmicznym

np dla j - 1 mamy policzone drzewo przedziałowe, w liściach trzymamy ? nie mogą być to poprzednie wartości
mamy 2 warunki sumy: l < i, al > ai
w iteracji j na indeksie i ma być liczba j-1 inwersji, kończących sie na i

Pseudokod:
for j = 2...k
    s = dp[][j - 1]
    n = dp[][j]
    t = puste drzewo przedziałowe czyli [0, ... 0]
    for i = 1...n
        w t zmieniamy wartość w liściu a[i]
        (czyli t[B + a[i]]) na s[i] czyli też aktualizujemy
        dodajemy do sumy, czyli n[i] = suma w t dla przedziału [a_i+1, n]

cp-algorithms.com -> segment tree
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
        dp[i][0] = 1;
    }

    int B = 1;
    while (B < n){
        B = B * 2;
    }    

    for(int j = 1; j < k; j++){
        int *t = new int[2 * B];
        for(int i = 1; i < 2 * B; i++){
            t[i] = 0;
        }
        for(int i = 0; i < n; i++){
            int suma = 0;
            int a = B + p[i] - 1;
            int b = 2 * B - 1;
            if(a < b){    
                suma = (suma + t[a]) % m;
                suma = (suma + t[b]) % m;
                while(a + 1 != b){
                    if(a % 2 == 0){
                        suma = (suma + t[a + 1]) % m;
                    }
                    if(b % 2 == 1){
                        suma = (suma + t[b - 1]) % m;
                    }
                    a = a/2;
                    b = b/2;
                }
            }
            
            dp[i][j] = suma;

            int x = B + p[i] - 1;
            t[x] = dp[i][j - 1];
            x = x / 2;
            while(x >= 1){
                t[x] = (t[x] + dp[i][j - 1]) % m;
                x = x / 2;
            }
        }
        delete [] t;
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
    delete [] p;

    return 0;
}