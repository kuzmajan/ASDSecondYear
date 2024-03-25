#include <iostream>
#include <vector>

using namespace std;

using Lli = long long int;
constexpr Lli MODULO = 1'000'000'000;


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);


    int n;
    cin >> n;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<Lli> konczySieNa(10001, 0);

    Lli sumaWszystkich = 0;
    for (int i = 0; i < n; i++) {
        konczySieNa[a[i]]++;
        sumaWszystkich++;
        Lli nowych = (((sumaWszystkich - konczySieNa[a[i]]) % MODULO) + MODULO) % MODULO;
        konczySieNa[a[i]] = sumaWszystkich;
        sumaWszystkich = (((sumaWszystkich + nowych) % MODULO) + MODULO) % MODULO;
    }

    cout << sumaWszystkich;

    return 0;
}