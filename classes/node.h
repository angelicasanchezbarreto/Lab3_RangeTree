#ifndef AVLTREE_NODE_H
#define AVLTREE_NODE_H

#include <utility>
using namespace std;

class AVLTree;
class RangeTree;

class Node {

    friend class AVLTree;
    friend class RangeTree;

protected:
    int key;
    pair<int,int> point;
    int height;
    Node* left;
    Node* right;

    //RangeTree YTree;

    Node() : left(nullptr), right(nullptr){};
    
public:

    void setSides(Node *left, Node *right){
        this->right=right;
        this->left=left;
    }
    Node(int key,pair<int,int> point){
        this->key=key;
        this->height=1;
        this->point=point;
        this->left=nullptr;
        this->right=nullptr;
    };

    Node(Node *node){
        this->height=node->height;
        this->key=node->key;
        this->left=node->left;
        this->right=node->right;
        this->point=node->point;
    }

};

#endif //AVLTREE_NODE_H
