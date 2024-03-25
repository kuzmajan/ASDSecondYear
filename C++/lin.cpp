#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

struct AVLNode {
    AVLNode *parent;
    AVLNode *leftChild;
    AVLNode *rightChild;
    long long key;
    int lheight;
    int rheight;
    int count;
    int countLeft;
    int countRight;
};

void RR(AVLNode *&root, AVLNode *current){
    AVLNode *right = current -> rightChild;
    AVLNode *par = current -> parent;
    current -> rightChild = right -> leftChild;
    if (current -> rightChild != nullptr){
        current -> rightChild -> parent = current;
    }
    right -> leftChild = current;
    right -> parent = par;
    current -> parent = right;

    current -> rheight = right -> lheight;
    current -> countRight = right -> countLeft;
    right -> lheight = std::max(1 + current -> lheight, 1 + current -> rheight);
    right -> countLeft = current -> count + current -> countLeft + current -> countRight;

    if (par != nullptr){
        if (par -> leftChild == current){
            par -> leftChild = right;
        }else{
            par -> rightChild = right;
        }
    }else{
        root = right;
    }
}

void LL(AVLNode *&root, AVLNode *current){
    AVLNode *left = current -> leftChild;
    AVLNode *par = current -> parent;
    current -> leftChild = left -> rightChild;
    if (current -> leftChild != nullptr){
        current -> leftChild -> parent = current;
    }
    left -> rightChild = current;
    left -> parent = par;
    current -> parent = left;

    current -> lheight = left -> rheight;
    current -> countLeft = left -> countRight;
    left -> rheight = std::max(1 + current -> lheight, 1 + current -> rheight);
    left -> countRight = current -> count + current -> countLeft + current -> countRight;

    if (par != nullptr){
        if (par -> leftChild == current){
            par -> leftChild = left;
        }else{
            par -> rightChild = left;
        }
    }else{
        root = left;
    }
}

void RL(AVLNode *&root, AVLNode *current){
    AVLNode *right = current -> rightChild;
    AVLNode *rightLeft = right -> leftChild;
    AVLNode *par = current -> parent;

    right -> leftChild = rightLeft -> rightChild;
    if (right -> leftChild != nullptr){
        right -> leftChild -> parent = right;
    }

    current -> rightChild = rightLeft -> leftChild;
    if(current -> rightChild != nullptr){
        current -> rightChild -> parent = current;
    }

    rightLeft -> leftChild = current;
    rightLeft -> rightChild = right;
    current -> parent = rightLeft;
    right -> parent = rightLeft;
    rightLeft -> parent = par;

    current -> rheight = rightLeft -> lheight;
    current -> countRight = rightLeft -> countLeft;
    right -> lheight = rightLeft -> rheight;
    right -> countLeft = rightLeft -> countRight;
    rightLeft -> lheight = std::max(1 + current -> lheight, 1 + current -> rheight);
    rightLeft -> countLeft = current -> count + current -> countLeft + current -> countRight;
    rightLeft -> rheight = std::max(1 + right -> lheight,  1 + right -> rheight);
    rightLeft -> countRight = right -> count + right -> countLeft + right -> countRight;

    if (par != nullptr){
        if (par -> leftChild == current){
            par -> leftChild = rightLeft;
        }else{
            par -> rightChild = rightLeft;
        }
    }else{
        root = rightLeft;
    }
}


void LR(AVLNode *&root, AVLNode *current){
    AVLNode *left = current -> leftChild;
    AVLNode *leftRight = left -> rightChild;
    AVLNode *par = current -> parent;

    left -> rightChild = leftRight -> leftChild;
    if (left -> rightChild != nullptr){
        left -> rightChild -> parent = left;
    }

    current -> leftChild = leftRight -> rightChild;
    if(current -> leftChild != nullptr){
        current -> leftChild -> parent = current;
    }

    leftRight -> rightChild = current;
    leftRight -> leftChild = left;
    current -> parent = leftRight;
    left -> parent = leftRight;
    leftRight -> parent = par;

    current -> lheight = leftRight -> rheight;
    current -> countLeft = leftRight -> countRight;
    left -> rheight = leftRight -> lheight;
    left -> countRight = leftRight -> countLeft;
    leftRight -> lheight = std::max(1 + left -> lheight, 1 + left -> rheight);
    leftRight -> countLeft = left -> count + left -> countLeft + left -> countRight;
    leftRight -> rheight = std::max(1 + current -> lheight, 1 + current -> rheight);
    leftRight -> countRight = current -> count + current -> countLeft + current -> countRight;

    if (par != nullptr){
        if (par -> leftChild == current){
            par -> leftChild = leftRight;
        }else{
            par -> rightChild = leftRight;
        }
    }else{
        root = leftRight;
    }
}

int countAVL(AVLNode *&root, long long k, bool countBigger){
    AVLNode *par;
    int bigger = 0;
    int smaller = 0;
    int all = 0;

    par = root;

    if (root != nullptr){
        all = root->count + root->countLeft + root->countRight;
        while (true) {
            if (k < par->key) {
                bigger += par->count + par->countRight;
                if (par->leftChild == nullptr) {
                    break;
                }
                par = par->leftChild;
            } else if (k == par->key) {
                bigger += par->countRight;
                smaller += par->countLeft;
                break;
            } else {
                smaller += par->count + par->countLeft;
                if (par->rightChild == nullptr) {
                    break;
                }
                par = par->rightChild;
            }
        }
    }
    if(countBigger){
        return all - bigger;
    }else{
        return -smaller;
    }
}

void insertAVL(AVLNode *&root, long long k){
    AVLNode *n, *child, *par;
    bool up;
    bool copy = false;
    n = new AVLNode;
    n -> leftChild = n -> rightChild = n -> parent = nullptr;
    n -> key = k;
    n -> lheight = -1;
    n -> rheight = -1;
    n -> count = 1;
    n -> countLeft = 0;
    n -> countRight = 0;

    par = root;

    if (root == nullptr){
        root = n;
    }else{
        while(true){
            if (k < par -> key){
                par -> countLeft += 1;
                if (par -> leftChild == nullptr){
                    par -> leftChild = n;
                    break;
                }
                par = par -> leftChild;
            }else if(k == par -> key){
                par -> count += 1;
                copy = true;
                delete n;
                break;
            }else{
                par -> countRight += 1;
                if (par -> rightChild == nullptr){
                    par -> rightChild = n;
                    break;
                }
                par = par -> rightChild;
            }
        }
        if (!copy){
            n -> parent = par;
            if(par -> lheight - par -> rheight != 0 ){
                par -> lheight = 0;
                par -> rheight = 0;
            }else{
                if(par -> leftChild == n){
                    par -> lheight = 0;
                }else{
                    par -> rheight = 0;
                }
                child = par;
                par = par -> parent;

                up = false;
                while(par != nullptr){
                    if(par -> lheight - par -> rheight != 0){
                        up = true;
                        break;
                    }
                    if(par -> leftChild == child){
                        par -> lheight += 1;
                    }else{
                        par -> rheight += 1;
                    }
                    child = par;
                    par = par -> parent;
                }

                if(up){
                    if(par -> lheight - par -> rheight == 1){
                        if(par -> rightChild == child){
                            par -> rheight += 1;
                        }else if(child -> lheight - child -> rheight == -1){
                            LR(root, par);
                        }else{
                            LL(root, par);
                        }
                    }else{
                        if (par -> leftChild == child){
                            par -> lheight += 1;
                        }else if(child -> lheight - child -> rheight == 1){
                            RL(root, par);
                        }else{
                            RR(root, par);
                        }
                    }
                }
            }
        }
    }
}

AVLNode * prevNode(AVLNode * p){
    AVLNode * rChild;
    if(p != nullptr){
        if(p -> leftChild != nullptr){
            p = p -> leftChild;
            while(p -> rightChild != nullptr){
                p = p -> rightChild;
            }
        }else {
            do{
                rChild = p;
                p = p -> parent;
            }while(p != nullptr && p -> rightChild != rChild);
        }
    }
    return p;
}

AVLNode * findBeforeDeleteWithDecrease (AVLNode * par, long long k, int num){
    while(par -> key != k){
        if (par -> key < k){
            par -> countRight -= num;
            par = par -> rightChild;
        }else{
            par -> countLeft -= num;
            par = par -> leftChild;
        }
    }
    par -> count -= num;
    return par;
}

AVLNode * deleteAVL(AVLNode * & root, long long var, bool second, AVLNode * & prev){
    AVLNode * x;
    int pom;
    if (second){
        x = prevNode(prev);
        pom = x -> count;
        x = findBeforeDeleteWithDecrease(prev,  x -> key, pom);
    }else{
        x = findBeforeDeleteWithDecrease(root, var, 1);
    }
    if (x -> count == 0){
        if (second){
            x -> count += pom;
            prev -> count += pom;
        }
        AVLNode  *t, *y, *z;
        bool nest;
        if(x -> leftChild != nullptr && x -> rightChild != nullptr){
            y = deleteAVL(root, var, true, x);
            nest = false;
        }else{
            if(x -> leftChild != nullptr){
                y = x -> leftChild;
                x -> leftChild = nullptr;
            }else{
                y = x -> rightChild;
                x -> rightChild = nullptr;
            }
            x -> lheight = -1;
            x -> rheight = -1;
            x -> countLeft = 0;
            x -> countRight = 0;
            nest  = true;
        }
        if (y != nullptr){
            y -> parent = x -> parent;
            y -> leftChild = x -> leftChild;
            if (y -> leftChild != nullptr){
                y -> leftChild -> parent = y;
            }
            y -> rightChild = x->rightChild;
            if (y -> rightChild != nullptr) {
                y->rightChild->parent = y;
            }
            y -> lheight = x -> lheight;
            y -> rheight = x -> rheight;
            y -> countLeft = x -> countLeft;
            y -> countRight = x -> countRight;
        }

        if(x -> parent){
            if(x -> parent -> leftChild == x ){
                x -> parent -> leftChild = y;
            }else{
                x -> parent -> rightChild = y;
            }
        }
        else root = y;

        if(nest){
            z = y;
            y = x -> parent;
            while(y != nullptr){
                if(!(y -> lheight - y -> rheight)){
                    if(y->leftChild == z){
                        y->lheight -= 1;
                    }else{
                        y->rheight -= 1;
                    }
                    break;
                }else{
                    if(((y -> lheight - y -> rheight == 1) && (y -> leftChild == z)) || ((y -> lheight - y -> rheight == -1) && (y -> rightChild == z))){
                        y -> lheight = y -> rheight = std::min(y -> lheight, y -> rheight);
                        z = y; y = y -> parent;
                    }else{
                        if(y -> leftChild == z){
                            t = y -> rightChild;
                        }else{
                            t = y -> leftChild;
                        }
                        if(!(t -> lheight - t -> rheight)){
                            if(y -> lheight - y -> rheight == 1){
                                y -> rheight -= 1;
                                LL(root, y);
                            }else{
                                y -> lheight -= 1;
                                RR(root, y);
                            }
                            break;
                        }else if(y -> lheight - y -> rheight == t -> lheight - t -> rheight){
                            if(y -> lheight - y -> rheight == 1){
                                y -> rheight -= 1;
                                LL(root, y);
                            }else{
                                y -> lheight -= 1;
                                RR(root, y);
                            }
                            z = t; y = t -> parent;
                        }
                        else{
                            if(y -> lheight - y -> rheight == 1){
                                y -> rheight -= 1;
                                LR(root, y);
                            }else{
                                y -> lheight -= 1;
                                RL(root, y);
                            }
                            z = y->parent; y = z->parent;
                        }
                    }
                }
            }
        }
    }
    return x;
}


void DFSRelease ( AVLNode * v ){
    if(v != nullptr)    {
        DFSRelease(v -> leftChild);
        DFSRelease (v -> rightChild );
        delete v;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long k;
    std::cin >> n;
    std::cin >> k;

    std::vector<std::tuple<long long, long long, long long>> input;
    long long x, y, z;
    input.reserve(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y >> z;
        input.emplace_back(x, y, z);
    }

    sort(input.begin(), input.end(), [](const std::tuple<long long, long long, long long>& a, const std::tuple<long long, long long, long long>& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    AVLNode *root1 = nullptr;
    AVLNode *root2 = nullptr;
    AVLNode *pom = nullptr;
    long long result = 0;
    int a = 0;
    for (int i = 0; i < n; i ++){
        while(std::abs(std::get<2>(input[i]) - std::get<2>(input[a])) > k){
            deleteAVL(root1, std::get<0>(input[a]), false, pom);
            deleteAVL(root2, std::get<1>(input[a]), false, pom);
            a++;
        }
        result += countAVL(root1, std::get<1>(input[i]), true);
        result += countAVL(root2, std::get<0>(input[i]), false);
        insertAVL(root1, std::get<0>(input[i]));
        insertAVL(root2, std::get<1>(input[i]));
    }
    std::cout<<result<<std::endl;

    DFSRelease(root1);
    DFSRelease(root2);
}
