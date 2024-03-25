/*
 LEX- porównywanie podsłów dane słowa
 [a,b]<[c,d]
 Pierwsze podejście- hashowanie
 Algorytm karpa-rabina
 Zamiana słów na liczby
 tekst t[1,...,n]  wzorzec p[1,...,m]
 Funkcja słowo -> liczba dla w != v h(w) = h(v) bardzo rzadko

 for i = 1,...,n - m + 1 (początki wzorca)
    if h(t[i,..,i+m-1]) = h(p) to prawie napewno znaleźliśmy
        if(t[i,...,i+m-1] == p) to znaleźliśmy (brutalnie porównujemy)

Jaka funkcja hashująca
 jeśli arytmetyka za darmo to c0 + c1b + c2b^2 +...+c _d-1 * b^d-1
 h^ to odwracamy cyferki, zamiast c0 - cd-1 to cd-1 - c0, wtedy zamieniamy dzielenie na mnożenie
 mniejsze liczby to modulo liczba pierwsza
 p > |rozmiar alfabetu|
 p < |rozmiar| < typ danych
 modulo p, b losowe od 1 do p-1

 mamy funkcje hashującą oraz dwa podsłowa
 liczymy w preproccessingu prefiksy w czasie liniowym
 h^(s[i,...,j]) = h(s[1,...,i-1])b^i-1)mod p
 porównujemy krótsze słowo i prefiks dłuższego
 binary search i hashowanie, żeby znaleźć pierwsze miejsce na którym sie różnią za pomocą, jak hase się zgadzają to liczymy dalej
Idea: wyszukujemy pierwsze miejsce na którym się różnia binarnie, czyli logn porównań hashy




 Drugie podejście- słownik podśłów bazowych (sparse table)
interesują nas tylko hashe podsłów których długość jest potęgą dwójki
 dla każdego k < logn liczymy hk(i), jesto to identyfikator słowa od i do i + 2^k
 preprocessing - nlogn, potem zapytania w czasei stałym
 jeśli s[i, ... i +2^k -1]) !- s[j, ... j+2^k -1] to hk(i)!=hk(j)
 id dla k = 0 to h0(i) = s[i]
 znając hk-1(i) dla każdego i  od 1 do n - 2^k - 1
 hk(i)
 budujemy tablice par hk-1(i), hk-1(i + 2^k-i), no i jeszcze i
 sortujemy leksykograficznie (radix sort liniowy)
 bierzemy nie logn porównań, tylko 2 razy- prefiks, sufiks













 */