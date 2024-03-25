#include <iostream>
#include <stdlib.h>

using namespace std;

/*
spróbować drzewa splay/treap -> łatwiejsze w implementacji
operacje na bst: find, insert, erase
splay i treap udostępniają też split, join, join(t1,t2), jeśli wszystkie key z t1 < niż t2, split(t,x), to powstajeą t1<x<t2

splay opisane na wikipedii, jest troche kodu
treap: cp-algorythims


insert(j,x,k)
k kopii elementu x przed indeks j

drzewa zrównoważone BST
kolejność w węzłach prefiksowy taka jak w ciągu

get: i < sl to w sl, i = sl + 1 to w węźle, inaczej w sr ale szukamy i - sl - 1
w węźle trzymam rozmiar poddrzewa


insert: robimy rotacje: void update(node*u){v->s = v->lewy-> + v->prawy->s + 1}
trzymamy jaką liczbę reprezentujemy
insert przed 3: schodzimy do lewego dziecka, a potem skrajnie w prawo dodajemy liść z k, aktualizujemy wszystkim rozmiar drzewa (suma liczby kopii w poddrzewie)
edge case: 55555 (3) 55555
rodzielamy na dwa
podmieniamy korzeń
lewe dzieci do lewego, prawy do prawego
*/

int main(){
    



    return 0;
}