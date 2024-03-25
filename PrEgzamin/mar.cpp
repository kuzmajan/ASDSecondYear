#include <iostream>
#include <vector>

int n, m;
std::vector<std::vector<int>> neighbours;
int *count;
bool *visited;
std::vector<int> path;
int* prev;

void dfs(int root){
    visited[root] = true;
    int i = 0;
    path.push_back(root);
    while(i < count[root]){
        if(!visited[neighbours[root][i]] && neighbours[root][i] != (n - 1)){
            if(prev[neighbours[root][i]] == -1){
                prev[neighbours[root][i]] = root;
            }
            dfs(neighbours[root][i]);
            path.push_back(root);
        }else if(neighbours[root][i] == (n - 1) && prev[neighbours[root][i] == -1]){
            prev[neighbours[root][i]] = root;
        }
        i++;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 0; i < n; i++){
        std::vector<int> temp;
        neighbours.push_back(temp);
    }
    count = new int[n];
    for (int i = 0; i < n; i++){
        count[i] = 0;
    }
    prev = new int[n];
    for (int i = 0; i < n; i++){
        prev[i] = -1;
    }
    for(int i = 0; i < m; i++){
        int a, b;
        std::cin >> a >> b;
        a = a - 1;
        b = b - 1;
        neighbours[a].push_back(b);
        count[a]++;
        neighbours[b].push_back(a);
        count[b]++;
    }
    visited = new bool[n];
    for (int i = 0; i < n; i++){
        visited[i] = false;
    }
    dfs(0);
//    for (int i : path){
//        std::cout<<i;
//    }
    std::vector<int> toN;
    int akt = n - 1;
    toN.push_back(akt);
    while(prev[akt] != 0){
        toN.push_back(prev[akt]);
        akt = prev[akt];
    }
    std::cout << path.size() + toN.size() << std::endl;
    for(int i : path){
        std::cout << i + 1 << " ";
    }
    for(int i = toN.size() - 1; i >= 0; i--){
        std::cout << toN[i] + 1 << " ";
    }

    delete[] prev;
    delete[] visited;
    delete[] count;

    return 0;
}