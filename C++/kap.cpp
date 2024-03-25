
/*
Dla nas odległość między (x1,y1) a (x2,y2) to min (|x1-x2|,|y1-y2|)
Dijkstra, ale mamy problem
Jeśli n wierzchołków, to mamy rzędu O(n^2) krawędzi

function dijkstra(G, S)
    for each vertex V in G
        dist[V] <- infinite
        prev[V] <- NULL
        If V != S, add V to Priority Queue Q
    dist[S] <- 0
    
    while Q IS NOT EMPTY
        U <- Extract MIN from Q
        if (dystans < neiskończoność){
            continue;
        }else{
            for each unvisited neighbour V of U 
                temperoryDist <- dist[U] + edgeWeight(U, V)
                if temperoryDist < dist[V]
                    dist[V] <- temperoryDist
                    prev[V] <- U
                    q.decreaseKey(v, dist[V]) -> zamiast robić dcrease key, to wrzucamy kopie wierzchołka w
                    jak ponownie go weźmiemy, a był już obsłużony, to go ignorujemy
                    czyli: q.push({d[v], v})
            i akutalizować visited
        }
    return dist[], prev[]

    W kolejce mamy<pair<odległość, identyfikator>>


Nie bierzemy wszystkich połączeń, czyli sortowanie po x, sortowanie po y, O(E+VlogV)
Jak zbudować listy sąsiedztwa?
Sortujemy wyspy po współrzędnej w kodzie
Sortujemy vector<tuple<int,int,int>>
Sortowanie po x, potem z inną fukcją po y
Inaczej: dwa wektory, vector<pair<int,int>> to x, id, vector<pair<int,int>> to y, id
To nam mówi do jakich wierzchołków robić krawędzie
*/
#include <climits>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <stdbool.h>
#include<algorithm>


using namespace std;

int main(){
    int n;
    cin >> n;
    int **p = new int*[n];
    vector<vector<int>> neighbours;
    vector<pair<int, int>> x;
    vector<pair<int, int>> y;
    for(int i = 0; i < n; i++){
        p[i] = new int[2];
        cin >> p[i][0];
        cin >> p[i][1];
        pair<int, int> x_act = {p[i][0], i};
        pair<int, int> y_act = {p[i][1], i};
        x.push_back(x_act);
        y.push_back(y_act);
        vector<int> act;
        neighbours.push_back(act);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    for(int i = 0; i < n - 1; i++){
        neighbours[x[i + 1].second].push_back(x[i].second);
        neighbours[y[i + 1].second].push_back(y[i].second);
        neighbours[x[i].second].push_back(x[i + 1].second);
        neighbours[y[i].second].push_back(y[i + 1].second);
    }
    neighbours[x[n - 1].second].push_back(x[n - 2].second);
    neighbours[y[n - 1].second].push_back(y[n - 2].second);
    //Mamy listę sąsiedztwa neighoburs, 
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0] = 0;

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        for (int x : neighbours[u]) {
            int weight = min(abs(p[u][0] - p[x][0]), abs(p[u][1] - p[x][1]));
            if (dist[x] > dist[u] + weight) {
                dist[x] = dist[u] + weight;
                q.push({-dist[x], x});
            }
        }
    }
    cout << dist[n-1];
    delete[] p;
    return 0;
}
