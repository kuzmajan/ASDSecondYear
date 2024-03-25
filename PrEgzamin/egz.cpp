//
// Created by kuzma on 01.02.2024.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    vector<pair<long long, long long>> poczatek;
    vector<pair<long long, long long>> koniec;
    poczatek.reserve(n);
    koniec.reserve(n);

    long long x,y,z;
    for (int i = 0; i < n; i++){
        cin >> x >> y >> z;
        poczatek.emplace_back(make_pair(x,z));
        koniec.emplace_back(make_pair(y,z));
    }

    sort(poczatek.begin(), poczatek.end());
    sort(koniec.begin(), koniec.end());

    int liczAkt = 0;
    int maxAkt = 0;
    long long maxIndeks = 0;
    map<long long, long long> krotnosc;

    long long p = 0;
    long long k = 0;
    long long pocz = 0;
    long long kon = 0;
    long long prezesP = 0;
    long long prezesK = 0;

    for(int i = 0; i < 2 * n - 1; i++){
        if(p < n){
            pocz = poczatek[p].first;
            prezesP = poczatek[p].second;
        }
        if(k < n){
            kon = koniec[k].first;
            prezesK = koniec[k].second;
        }
        if(p < n && k < n){
            if(pocz < kon){
                auto prez = krotnosc.find(prezesP);
                if (prez->first != prezesP){
                    krotnosc.insert(make_pair(prezesP, 1));
                    liczAkt++;
                    if (liczAkt > maxAkt){
                        maxAkt = liczAkt;
                        maxIndeks = pocz;
                    }
                }else{
                    prez->second = prez->second + 1;
                }
                p++;
            }else{
                auto prez = krotnosc.find(prezesK);
                if (prez -> second == 1){
                    krotnosc.erase(prez);
                    liczAkt--;
                }else{
                    prez -> second = prez -> second - 1;
                }
                k++;
            }
        }else if(p < n){
            auto prez = krotnosc.find(prezesP);
            if (prez->first != prezesP){
                krotnosc.insert(make_pair(prezesP, 1));
                liczAkt++;
                if (liczAkt > maxAkt){
                    maxAkt = liczAkt;
                    maxIndeks = pocz;
                }
            }else{
                prez->second = prez->second + 1;
            }
            p++;
        }else{
            k++;
        }
    }
    cout << maxIndeks << " " << maxAkt << endl;
    return 0;
}