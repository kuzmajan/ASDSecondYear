

/*
Wejście- graf skierowany, zależności między projektami, każdy projekt ma koszt.
Graf podany jako lista krawędzi.
n - liczba projektów, 
m - liczba zależności (krawędzi)
k - liczba projektów do zrealizowania
5 3 3 
10
500
150
200
100
1 2
1 3
4 5
*zależności między projektami nie tworzą cykli, czyli graf to DAG

OPT- rozwiązanie optymalne
Najtańszy wierzchołek v*
Obserwacja: opt - v* musi zawierać projekt o koszcie >= v*, czyli wybranie v* jest bezpieczne
Wybieramy zawsze najtańszy wierzchołek stopnia wejściowego 0, projekt który nie wymaga innego do zrobienia wcześniej
Alg:
    oblicz tablicę indeg[],  O(n + m)
    utwórz kolejkę priorytetową z elementów o stopniu 0 O(n)
    for i = 1,...,k
        weź nastańszy wierzchołek stopnia wchodzącego 0 v* (p.top, p.pop - biore, usuwam) O(logn)
        usuń v* z grafu (usuwamy wierzchołek, patrzymy na krawędzie wychodzące, zmniejszamy stopień, jeśli zmalał do 0, to wstawiamy do kolejki), czyli:
        for (auto w: sąsiedzi[v]){ O(outdeg[v])*(O(logn))
            --indeg[w]
            if (indeg[v] == 0){
                włóż do kolejki
            }
        }
Czyli potencjalnie nklogn
O(m+n  + klogn + m + nlogn)

Reprezentacja: dla każdego wierzchołka mamy wektor sąsiedzi(v) zawierający wszystkie takie w, że (v,w) in E
Czyli listy sąsiedztwa z uzyciem vektorów

Możemy liczyć ile do danego wierzchołka wchodzi krawędzi
Jeśli 0, to jest on stopnia wejściowego 0
Kolejka prioretytowa z tych elementów:
przechowywyujemy wierzchołki ze stopniem wejściowym 0
usuwanie elementu, dodawanie, zwaracanie minimum
w c++ kolejka prioretytowa jako kopiec zupełny: priority_queue
priority_queue<t> q: kopiec typu max przechowywujący elementy typu t
chcemy przechowywać parę typu wierzchołęk, koszt, czyli
priority_queue<pair<int,int>>

tylko jak zamienić max na min?
przemnożyć wszystko *(-1)

inaczej: można przekazać funkcję (klasę) porównującą elementy
typedef ii pair<int,int>;
priority_queue<ii, vector<ii>, greater<ii>>,


*/


/*

Inaczej- liniowe sortowanie topologiczne grafu
zliczamy wchodzące krawędzie
dla zwykłej kolejki wrzucamy stopnia 0
n razy wrzucamy wierzchołek, zmniejszamy stopnie sąsiadów
zawsze pierwszy któy weźmiemy będzie miał wage 0
*/

#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include <queue>


using namespace std;

int main(){
    int n, m, k;
    cin >> n;
    cin >> m;
    cin >> k;  
    int *indeg = new int[n];
    int *price = new int[n];
    vector<vector<int>> neighbours;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        price[i] = -x;
        indeg[i] = 0;
        vector<int> act;
        neighbours.push_back(act);
    }
    for (int i = 0; i < m; i++){
        int x, y;
        cin >> x;
        cin >> y;
        neighbours[y - 1].push_back(x - 1);
        ++indeg[x - 1];
    }
    priority_queue<pair<int, int>> q;
    for (int i = 0; i < n; i++){
        if (indeg[i] == 0){
            pair<int, int> p;
            p.first = price[i];
            p.second = i;
            q.push(p);
        }
    }
    for (int i = 0; i < k; i++){
        pair<int,int> act = q.top();
        q.pop();
        result = max(result, -act.first);
        for (auto w: neighbours[act.second]){
            indeg[w]--;
            if (indeg[w] == 0){
                pair<int, int> p;
                p.first = price[w];
                p.second = w;
                q.push(p);
            }
        }
    }
    cout << result;
    return 0;
}


