#include "avltree.h"

using namespace std;

typedef pair<int,int> pairInt;
typedef vector<pairInt> vecPairInt;

class RangeTree {
    public:
        bool insert(pair<int,int> point);
        vecPairInt searchQuery(pairInt begin,pairInt end);
        RangeTree(){};
    protected:
        Node* searchFather(Node *&node, int key);
        void insertCoordinate(RangeTree *tree,pairInt point, bool coord);
        Node* updateYTree(Node* temp,pairInt point);
        void search(Node*& temp, int begin, int end, vecPairInt& points);
    private:
        AVLTree mainTree;

};

Node* RangeTree::searchFather(Node *&node, int key){
    if(node == NULL || node->right && node->right->key == key 
    || node->left && node->left->key == key)
        return node;
    else if(key > node->key)
        return searchFather(node->right, key);
    else if(key <= node->key)
        return searchFather(node->left, key);
    return node;
}


bool RangeTree::insert(pairInt point){
    insertCoordinate(this,point,true);
    //Node* current = mainTree.root;
    //updateYTree(current, point);
    return true;
}

void RangeTree::insertCoordinate(RangeTree *tree,pairInt point, bool coord){
    int coordinate;
    if(coord) coordinate = point.first;
    else coordinate = point.second;

    if(tree->mainTree.empty()){
        tree->mainTree.insert(coordinate, point);
    } else{
        tree->mainTree.counter++;
        tree->mainTree.insert(coordinate, point);
        auto temp = tree->mainTree.root;
        auto father = searchFather(temp,coordinate);
        tree->mainTree.counter++;
        if(father->right && father->right->key == coordinate){
            tree->mainTree.insert(father->key,father->point);
        } 
        else if(father->left && father->left->key == coordinate){
            tree->mainTree.insert(coordinate,point);
        }
    }
    tree->mainTree.counter=0;
}

void RangeTree::search(Node*& temp, int begin, int end,vecPairInt& points){
    if(!temp->right && !temp->left){
        if(temp->key >= begin && temp->key <= end)
            points.push_back(temp->point);
    } else if(begin > temp->key && end > temp->key){
        search(temp->right,begin,end,points);
    } else if(begin <= temp->key && end <= temp->key){
        search(temp->left, begin, end, points);
    } else if(begin <= temp->key && end > temp->key){
        search(temp->left, begin, end, points);
        search(temp->right, begin, end, points);
    }
}

vecPairInt RangeTree::searchQuery(pairInt begin,pairInt end){
    vecPairInt points;
    Node* temp = mainTree.root;
    search(temp, begin.first, end.first, points);
    return points;
}

/* Node* RangeTree::updateYTree(Node* temp,pair<int,int> point){
    if(temp){
        if(temp->right && temp->right->key == point.first 
        || temp->left && temp->left->key == point.first){
            insertCoordinate(temp->YTree,point,false);
        } else {
            updateYTree(temp->right,point);
            updateYTree(temp->left,point);
        }
    }
    return temp;
} */
