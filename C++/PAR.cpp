#include <iostream>
#include <cmath>
#include <vector>

void dfsHeight(int *left, int *right, int**&height, int cur){
    int l, r;
    height[cur] = new int[2];
    if (left[cur] == -2 && right[cur] == -2){
        height[cur][0] = 0;
        height[cur][1] = cur;
    }else {
        if (left[cur] >= 0) {
            dfsHeight(left, right, height, left[cur]);
            l = height[left[cur]][0];
        } else {
            l = -1;
        }
        if (right[cur] >= 0) {
            dfsHeight(left, right, height, right[cur]);
            r = height[right[cur]][0];
        } else {
            r = -1;
        }
        if(l > r){
            height[cur][0] = 1 + l;
            height[cur][1] = height[left[cur]][1];
        }else{
            height[cur][0] = 1 + r;
            height[cur][1] = height[right[cur]][1];
        }
    }
}
//Na pierwszej pozycji pary wysokość, na drugiej wierzchołek.

void dfsUp(int *left, int *right, int *parent, int**&up, int** height, int cur, int*&depth){
    up[cur] = new int[2];
    if (cur == 0){
        up[0][0] = 0;
        up[0][1] = cur;
        depth[cur] = 0;
    }else {
        depth[cur] = depth[parent[cur]] + 1;
        bool isLeft = true;
        if(cur == right[parent[cur]]){
            isLeft = false;
        }
        if (isLeft){
            if (right[parent[cur]] > 0){
                if(1 + up[parent[cur]][0] > 2 + height[right[parent[cur]]][0]){
                    up[cur][0] = 1 + up[parent[cur]][0];
                    up[cur][1] = up[parent[cur]][1];
                }else{
                    up[cur][0] = 2 + height[right[parent[cur]]][0];
                    up[cur][1] = height[right[parent[cur]]][1];
                }
            }else{
                up[cur][0] = 1 + up[parent[cur]][0];
                up[cur][1] = up[parent[cur]][1];
            }
        }else{
            if (left[parent[cur]] > 0){
                if(1 + up[parent[cur]][0] > 2 + height[left[parent[cur]]][0]){
                    up[cur][0] = 1 + up[parent[cur]][0];
                    up[cur][1] = up[parent[cur]][1];
                }else{
                    up[cur][0] = 2 + height[left[parent[cur]]][0];
                    up[cur][1] = height[left[parent[cur]]][1];
                }
            }else{
                up[cur][0] = 1 + up[parent[cur]][0];
                up[cur][1] = up[parent[cur]][1];
            }
        }
    }
    if (left[cur] >= 0){
        dfsUp(left, right, parent, up, height, left[cur], depth);
    }
    if (right[cur] >= 0){
        dfsUp(left, right, parent, up, height, right[cur], depth);
    }
}

void makePathsUp(int **&links, int n, int *parent){
    for (int i = 0; i <= std::floor(log2(n)); i++){
        for (int v = 0; v < n; v++){
            if(i == 0){
                links[i][v] = parent[v];
            }else{
                if(links[i - 1][v] != -1){
                    links[i][v] = links[i - 1][links[i - 1][v]];
                }else{
                    links[i][v] = -1;
                }
            }
        }
    }
}

int goUp(int v, int len, int n, int** links){
    int result = v;
    int i = std::floor(log2(n));
    while (len > 0){
        if ((1<<i) > len){
            i--;
        }else{
            result = links[i][result];
            len = len - (1<<i);
        }
    }
    return result;
}

int lca(int w, int v, int *parent, int** links, int n, int* depth){

    int wHeight = depth[w];
    int vHeight = depth[v];
    if (vHeight > wHeight){
        v = goUp(v, vHeight - wHeight, n, links);
    }else if (vHeight < wHeight){
        w = goUp(w, wHeight - vHeight, n, links);
    }
    if (w == v){
        return w;
    }
    int i = std::floor(log2(n));
    while (i >= 0){
        if (links[i][w] != links[i][v]){
            w = links[i][w];
            v = links[i][v];
        }
        i = i - 1;
    }
    return parent[w];
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    int *left = new int[n];
    int *right = new int[n];
    int *parent = new int[n];
    parent[0] = -1;

    for (int i = 0; i < n; i++){
        std::cin >> left[i];
        std::cin >> right[i];
        right[i]--;                 //teraz nulle to -2 !!!
        left[i]--;
        if (right[i] >= 0){
            parent[right[i]] = i;
        }
        if (left[i] >= 0){
            parent[left[i]] = i;
        }
    }

    int *depth = new int[n];

    int **height = new int*[n];
    dfsHeight(left, right, height, 0);

    int **up = new int*[n];
    dfsUp(left, right, parent, up, height, 0, depth);

    std::vector<std::pair<int, int>> maxPath;
    for(int i = 0; i < n; i++){
        if (height[i][0] > up[i][0]){
            maxPath.emplace_back(height[i][0], height[i][1]);
        }else{
            maxPath.emplace_back(up[i][0], up[i][1]);
        }

    }

    for (int i = 0; i < n; i++){
        delete [] height[i];
    }
    delete[] height;
    for (int i = 0; i < n; i++){
        delete [] up[i];
    }
    delete[] up;

    int p = std::floor(log2(n));
    int** links = new int*[p + 1];
    for (int i = 0; i <= p; i++){
        links[i] = new int[n];
    }

    makePathsUp(links, n, parent);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++){
        int a, b;
        std::cin >> a >> b;
        a--;
        std::pair<int, int> cur = maxPath[a]; //w parze mam teraz najdłuższy dystans, oraz najdalszy wierzchołek
        if (b > cur.first){
            std::cout << -1 << std::endl;
        }else{
            int ancestor = lca(a, cur.second, parent, links, n, depth);
            int len1 = depth[a] - depth[ancestor];
            if (b <= len1){
                std::cout << goUp(a, b, n, links) + 1 << std::endl;
            }else{
                std::cout << goUp(cur.second, cur.first - b, n, links) + 1 << std::endl;
            }
        }
    }



    for(int i = 0; i <= p; i++){
        delete [] links[i];
    }
    delete[] links;
    delete[] left;
    delete[] right;
    delete[] parent;
    delete[] depth;

    return 0;
}