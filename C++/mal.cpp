/*
Malowanie autostrady
Set, albo drzewo przedziałowe

Sety to trzymam set z przedziałami postaci (a,b), gdzie a to początek, b to koniec przedziału, tylko kolor biały
Jak dodaje czarny, to usuwam wszystkie zawierające się w nim, skracam końcowe (jeśli są białe).
Jak dodaje biały, usuwam wszystkie zawierające się w nim, licze krańce, dodaje jeden duży.
set<pair<int, int>> s: pary początek,koniec jednego koloru, automatycznie set porównuje po pierwzszej współżędnej

Mapy????:
Podobnie jak sety
Tylko mapa <miejsce, początek przedziału C/B>, czyli C, , ,B, ,C, , ,B, ,
                                                    C, C, C, B, B, C, C, C, B, B

                                                    Ale sety lepsze :))

Drzewa przedziałowe:
Inaczej niż w KIN!!!
Liście- elementy autostrady
Tworzymy pełne drzewo binarne
Wierzchołek ma kolor- ale ma go tylko wtedy, jeśli cały przedział pod nim jest tego koloru
Idziemy do góy, kolor to ostatni kolor, który nie był mieszany
albo w  dół, pierwszy którym nie był mieszany
Akutalizacja: wspólny przodek, idziemy do niego, aktualizujemy odpowiednie rodzeństwo na nasz kolor
Spychanie przy aktualziacji, czyli update rodzeństwa
licznik odcinków białych:
2 drzewa przedziałwoe, kolor, ile
ile(i) to ile odcinkó białych jest w węźle reprezentowanym przez i, 
ile to 2^n albo 0
*/

/*
    Sety to trzymam set z przedziałami postaci (a,b), gdzie a to początek, b to koniec przedziału, tylko kolor biały
    Jak dodaje czarny, to usuwam wszystkie zawierające się w nim, skracam końcowe (jeśli są białe).
    Jak dodaje biały, usuwam wszystkie zawierające się w nim, licze krańce, dodaje jeden duży.
    set<pair<int, int>> s: pary początek,koniec jednego koloru, automatycznie set porównuje po pierwzszej współżędnej
    */



#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <set>
#include <utility>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    int n;
    int m;
    cin >> n;
    cin >> m;
    set<pair<int, int>> s;
    int begin, end;
    char color;
    pair<int, int> act;
    int licznik = 0;
    for(int i = 0; i < m; i++){
        cin >> act.first;
        cin >> act.second;
        cin >> color;
        if (color == 'B'){
            if (s.empty()){
                s.insert(act);
                licznik += act.second - act.first + 1;
            }else{
                auto it = s.lower_bound(act);
                if (it != s.begin()){
                    it--;
                    if ((*it).second >= act.first){
                        act.first = (*it).first;
                        act.second = max((*it).second, act.second); 
                        licznik -= (*it).second - (*it).first + 1;
                        s.erase(it);
                    }
                    it = s.lower_bound(act);
                }                
                while (it != s.end() && (*it).second < act.second){
                    auto it2 = it;
                    it++;
                    licznik -= (*it2).second - (*it2).first + 1;
                    s.erase(it2);
                }
                if (it != s.end()){
                    if ((*it).first <= act.second){
                        act.second = (*it).second;
                        licznik -= (*it).second - (*it).first + 1;
                        s.erase(it);
                    }
                }
                s.insert(act); 
                licznik += act.second - act.first + 1;            
            }               
        }else{
            if (!s.empty()){
                auto it = s.lower_bound(act);               
                
                if (it != s.begin()){
                    it--;
                    if ((*it).second >= act.first){
                        if ((*it).second <= act.second){
                            pair<int, int> newPair;
                            newPair.first = (*it).first;
                            newPair.second = act.first - 1;
                            licznik -= (*it).second - (*it).first + 1;
                            s.erase(it);
                            if (newPair.first <= newPair.second){
                                s.insert(newPair);
                                licznik += newPair.second - newPair.first + 1;
                            }                            
                        }else{
                            pair<int, int> newPair1, newPair2;
                            newPair1.first = (*it).first;
                            newPair1.second = act.first - 1;
                            newPair2.first = act.second + 1;
                            newPair2.second = (*it).second;
                            licznik -= (*it).second - (*it).first + 1;
                            s.erase(it);
                            if (newPair1.first <= newPair1.second){
                                s.insert(newPair1);
                                licznik += newPair1.second - newPair1.first + 1;
                            }
                            if (newPair2.first <= newPair2.second){
                                s.insert(newPair2);
                                licznik += newPair2.second - newPair2.first + 1;
                            }
                        }
                       
                    }
                    it = s.lower_bound(act);
                }                
                while (it != s.end() && (*it).second < act.second){
                    auto it2 = it;
                    it++;
                    licznik -= (*it2).second - (*it2).first + 1;
                    s.erase(it2);
                }
                if (it != s.end()){
                    if ((*it).first <= act.second){
                        pair<int, int> newPair;
                        newPair.first = act.second + 1;
                        newPair.second = (*it).second;
                        licznik -= (*it).second - (*it).first + 1;
                        s.erase(it);
                        if (newPair.first <= newPair.second){
                            s.insert(newPair);
                            licznik += newPair.second - newPair.first + 1;
                        }
                    }
                }             
            } 
        }
        cout << licznik << endl;

    }

    return 0;
}