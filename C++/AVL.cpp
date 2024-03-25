#include <iostream>
#include <stdbool.h>

#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct AVLNode {
  AVLNode *parent;
  AVLNode *leftChild;
  AVLNode *rightChild;
  int key;
  int lheight;
  int rheight;
};



void printBT (string sp, string sn, AVLNode * v, string cr, string cl, string cp)
{
  string s;
  if( v )
  {
    s = sp;
    if( sn == cr ) s [ s.length( ) - 2 ] = ' ';
    printBT ( s + cp, cr, v->rightChild, cr, cl, cp);

    s = s.substr ( 0, sp.length( )-2 );
    cout << s << sn << v->key << ":" << v->lheight - v->rheight << endl;

    s = sp;
    if( sn == cl ) s [ s.length( ) - 2 ] = ' ';
    printBT ( s + cp, cl, v->leftChild, cr, cl, cp );
  }
}


void RR(AVLNode *&root, AVLNode *current){
    AVLNode *right = current -> rightChild;
    AVLNode *par = current -> parent;
    current -> rightChild = right -> leftChild;
    if (current -> rightChild != NULL){
        current -> rightChild -> parent = current;
    }
    right -> leftChild = current;
    right -> parent = par;
    current -> parent = right;

    current -> rheight = right -> lheight;
    right -> lheight = max(1 + current -> lheight, 1 + current -> rheight);

    if (par != NULL){
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
    if (current -> leftChild != NULL){
        current -> leftChild -> parent = current;
    }
    left -> rightChild = current;
    left -> parent = par;
    current -> parent = left;

    current -> lheight = left -> rheight;
    left -> rheight = max(1 + current -> lheight, 1 + current -> rheight); 

    if (par != NULL){
        if (par -> leftChild == current){
            par -> leftChild = left;
        }else{
            par -> rightChild = left;
        }
    }else{
        root = left;
    }
    //Czy tutaj aktualizować bf?    
}

void RL(AVLNode *&root, AVLNode *current){
    AVLNode *right = current -> rightChild;
    AVLNode *rightLeft = right -> leftChild;
    AVLNode *par = current -> parent;

    right -> leftChild = rightLeft -> rightChild;
    if (right -> leftChild != NULL){
        right -> leftChild -> parent = right;
    }

    current -> rightChild = rightLeft -> leftChild;
    if(current -> rightChild != NULL){
        current -> rightChild -> parent = current;
    }

    rightLeft -> leftChild = current;
    rightLeft -> rightChild = right;
    current -> parent = rightLeft;
    right -> parent = rightLeft;
    rightLeft -> parent = par;

    current -> rheight = rightLeft -> lheight;
    right -> lheight = rightLeft -> rheight;
    rightLeft -> lheight = max(1 + current -> lheight, 1 + current -> rheight);
    rightLeft -> rheight = max(1 + right -> lheight,  1 + right -> rheight);

    if (par != NULL){
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
    if (left -> rightChild != NULL){
        left -> rightChild -> parent = left;
    }

    current -> leftChild = leftRight -> rightChild;
    if(current -> leftChild != NULL){
        current -> leftChild -> parent = current;
    }

    leftRight -> rightChild = current;
    leftRight -> leftChild = left;
    current -> parent = leftRight;
    left -> parent = leftRight;
    leftRight -> parent = par;

    current -> lheight = leftRight -> rheight;
    left -> rheight = leftRight -> lheight;
    leftRight -> lheight = max(1 + left -> lheight, 1 + left -> rheight);
    leftRight -> rheight = max(1 + current -> lheight, 1 + current -> rheight);

    if (par != NULL){
        if (par -> leftChild == current){
            par -> leftChild = leftRight;
        }else{
            par -> rightChild = leftRight;
        }
    }else{
        root = leftRight;
    }
}


void insertAVL(AVLNode *&root, int k){
    AVLNode *n, *child, *par;
    bool t;

    n = new AVLNode;
    n -> leftChild = n -> rightChild = n -> parent = NULL;
    n -> key = k;
    n -> lheight = -1;
    n -> rheight = -1;
    
    par = root;

    if (root == NULL){
        root = n;
    }else{
        while(true){
            if (k < par -> key){
                if (par -> leftChild == NULL){
                    par -> leftChild = n;
                    break;
                }
                par = par -> leftChild;
            }else{
                if (par -> rightChild == NULL){
                    par -> rightChild = n;
                    break;
                }
                par = par -> rightChild;
            }
        }
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

            t = false;
            while(par != NULL){
                if(par -> lheight - par -> rheight != 0){
                    t = true;
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

            if(t){
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

int main(void){
    string cr, cl, cp;
    int Tk [ 32 ];   // tablica kluczy węzłów
    int i, x, i1, i2;
    AVLNode * root = NULL;
    int **p = new int*[n];

    cr = cl = cp = "  ";
    cr [ 0 ] = 218; cr [ 1 ] = 196;
    cl [ 0 ] = 192; cl [ 1 ] = 196;
    cp [ 0 ] = 179;

    srand ( time ( NULL ) );    // inicjujemy generator pseudolosowy

    for( i = 0; i < 32; i++ )   // Tablicę wypełniamy wartościami kluczy
        Tk [ i ] = i + 1;

    for( i = 0; i < 300; i++ )  // Mieszamy tablicę
    {
        i1 = rand( ) % 32;        // Losujemy 2 indeksy
        i2 = rand( ) % 32;

        x = Tk [ i1 ];            // Wymieniamy Tk [ i1 ] <--> Tk [ i2 ] 
        Tk [ i1 ] = Tk [ i2 ];
        Tk [ i2 ] = x;
    }

    for( i = 0; i < 32; i++ )   // Na podstawie tablicy tworzymy drzewo AVL
    {
        cout << Tk [ i ] << " ";
        insertAVL ( root, Tk [ i ] );
    }
    cout << endl << endl;

    printBT ( "", "", root, cr, cl, cp );   // Wyświetlamy zawartość drzewa AVL

    cout << endl << endl;

    for( i = 0; i < 300; i++ )  // Ponownie mieszamy tablicę
    {
        i1 = rand( ) % 32; i2 = rand( ) % 32;
        x = Tk [ i1 ]; Tk [ i1 ] = Tk [ i2 ]; Tk [ i2 ] = x;
    }

    // for( i = 0; i < 15; i++ )   // Usuwamy 15 węzłów
    // {
    //     cout << Tk [ i ] << " ";
    //     removeAVL ( root, findAVL ( root, Tk [ i ] ) );
    // }

    cout << endl << endl;

    printBT ( "", "", root, cr, cl, cp);   // Wyświetlamy zawartość drzewa AVL
}



