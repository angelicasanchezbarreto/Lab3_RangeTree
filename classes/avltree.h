#ifndef AVLTREE_H
#define AVLTREE_H

#include "node.h"

class RangeTree;

class AVLTree {

    friend class RangeTree;
    
protected:
    Node *root;
    int nodes;
    int counter=0;

    Node *insert(Node *&node, Node *&newNode);
    Node *search(Node *&node, int key);
    void clear(Node *node);
    void swapData(Node *parent, Node *child);
    int getKey(Node *node);

    int heightDifference(Node* right, Node* left);
    bool isBalanced(Node* right, Node* left);
    int compareHeights(Node*& node);
    int setHeight(Node *node);
    void rightRightRotation(Node* node);
    void leftLeftRotation(Node* node);
    void rightLeftRotation(Node* node);
    void leftRightRotation(Node* node);
    void inOrder(Node *nodo);

public:
    //AVLTree():root(nullptr),nodes(0) {};
    AVLTree(){
        root=nullptr;
        nodes=0;
    }

    bool insert(int key,pair<int,int> point);
    bool hasKey(int key);
    int size();
    bool empty();
    void printTree();
    ~AVLTree();

};


int AVLTree::getKey(Node *node){
    if(!node) return 0;
    else return node->key;
}


void AVLTree::inOrder(Node *nodo){
    if(nodo) {
        inOrder(nodo->left);
        cout << nodo->key << " ";
        inOrder(nodo->right);
    }
}


void AVLTree::printTree() {
    inOrder(root);
}


Node* AVLTree::insert(Node *&node, Node *&newNode){
    if(!node){
        node = newNode;
        return node;
    }
    else if(newNode->key > node->key){
        node->right = insert(node->right,newNode);
    }
    else if(newNode->key <= node->key){
        node->left = insert(node->left, newNode);
    }
    auto temp = node;
    temp->height = setHeight(temp);

    int checkBalanceRoot = compareHeights(temp);
    int checkBalanceRight = compareHeights(temp->right);
    int checkBalanceLeft = compareHeights(temp->left);

    if(temp->height<=3 || counter==2){
        if(checkBalanceRoot==2 && checkBalanceRight==1)
            leftLeftRotation(temp);
        else if(checkBalanceRoot==2 && checkBalanceRight==-1)
            rightLeftRotation(temp);
        else if(checkBalanceRoot==-2 && checkBalanceLeft==-1)
            rightRightRotation(temp);
        else if(checkBalanceRoot==-2 && checkBalanceLeft==1)
            leftRightRotation(temp);
    }
    return node;
}


Node* AVLTree::search(Node *&node, int key){
    if(node == NULL || key == node->key)
        return node;
    else if(key > node->key)
        return search(node->right, key);
    else
        return search(node->left, key);
}


void AVLTree::clear(Node *node){
    if(node){
        if(node->left)
            clear(node->left);
        if(node->right)
            clear(node->right);
        --nodes;
        //free(node);
        delete node;
        //remove(node->key);
    }
}


void AVLTree::swapData(Node *parent, Node *child){
    Node temp(*parent);
    parent->key = child->key;
    parent->height = child->height;
    parent->point = child->point;
    child->key = temp.key;
    child->height = temp.height;
}


int AVLTree::setHeight(Node *node){
    if(node->right && node->left){
        if(node->right->height > node->left->height)
            return node->right->height + 1;
        else
            return node->left->height + 1;
    } else {
        if(node->right) return node->right->height + 1;
        else if(node->left) return node->left->height + 1;
    }
    return 1;
}


bool AVLTree::insert(int key, pair<int,int> point) {
    auto newNode = new Node(key,point);
    insert(this->root,newNode);
    nodes++;
    return true;
}

void AVLTree::leftLeftRotation(Node* node){
    auto tempRoot = new Node(node->key,node->point);
    if(node->right->left)
        tempRoot->setSides(node->left,node->right->left);
    else tempRoot->setSides(node->left,nullptr);

    swapData(node,node->right);
    node->left = tempRoot;

    auto temp = node->right->right;
    node->right->right = nullptr;
    node->right->height = setHeight(node->right);
    node->left->height = setHeight(node->left);
    node->right = temp;
}


void AVLTree::rightRightRotation(Node* node){
    auto tempRoot = new Node(node->key,node->point);
    if(node->left->right)
        tempRoot->setSides(node->left->right,node->right);
    else tempRoot->setSides(nullptr,node->right);

    swapData(node,node->left);
    node->right = tempRoot;

    auto temp = node->left->left;
    node->left->left = nullptr;
    node->right->height = setHeight(node->right);
    node->left->height = setHeight(node->left);
    node->left = temp;
}


void AVLTree::rightLeftRotation(Node* node){
    rightRightRotation(node->right);
    node->right->height = setHeight(node->right);
    leftLeftRotation(node);
    node->height = setHeight(node);
}


void AVLTree::leftRightRotation(Node* node){
    leftLeftRotation(node->left);
    node->left->height = setHeight(node->left);
    rightRightRotation(node);
    node->height = setHeight(node);
}


int AVLTree::heightDifference(Node* right, Node* left){
    if(right && left)
        return right->height - left->height;
    else if(right)
        return right->height;
    else if(left)
        return -left->height;
    return 0;
}


bool AVLTree::isBalanced(Node* right, Node* left){
    if(right && left)
        return right->height - left->height == 0 || abs(right->height - left->height) == 1;
    else if(right)
        return right->height == 1;
    else if(left)
        return left->height == 1;
    return false;
}


int AVLTree::compareHeights(Node* &node){
    if(node){
        if(node->right && node->left){
            return heightDifference(node->right,node->left);
        } else {
            if(node->right){
                return heightDifference(node->right,node->left);
            }
            else if(node->left){
                return heightDifference(node->right,node->left);
            }
        }
    }
    return 0;
}


int AVLTree::size() {
    return nodes;
}


bool AVLTree::empty() {
    return nodes==0;
}


AVLTree::~AVLTree() {
    auto temp = root;
    clear(temp);
}


#endif //AVLTREE_H
