#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int l_przedzialow, dl, p, k;
    string tekst;
    cin >> dl >> l_przedzialow;
    cin >> tekst;

    vector<pair<int, int>> przedzialy;
    przedzialy.reserve(l_przedzialow);

    for (int i = 0; i < l_przedzialow; i++) {
        cin >> p >> k;
        przedzialy.emplace_back(make_pair(p, k));
    }

    sort(przedzialy.begin(), przedzialy.end());


    int a, b;
    for (int i = 0; i < l_przedzialow; i++) {
        bool czy_zamiana = true;
        a = przedzialy[i].first;
        b = przedzialy[i].second;

        while (a < b) {
            if (czy_zamiana) {
//                cout << "zamieniam " << a << " " << b << endl;
                char pom = tekst[a - 1];
                tekst[a - 1] = tekst[b - 1];
                tekst[b - 1] = pom;
            }

            a++;
            b--;
            if (i + 1 < l_przedzialow && a == przedzialy[i + 1].first && (przedzialy[i + 1].first + przedzialy[i + 1].second == a + b)) {
                czy_zamiana = !czy_zamiana;
                i++; // bo odwiedzilismy kolejny przedzial
            }
        }
    }

    cout << tekst << "\n";

    return 0;
}