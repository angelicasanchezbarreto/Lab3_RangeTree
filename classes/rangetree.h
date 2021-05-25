#pragma once

#include "avltree.h"
#include <map>

using namespace std;

class Node;

typedef pair<int,int> pairInt;
typedef vector<pairInt> vecPairInt;
typedef vector<Node*> vecNode;

class RangeTree{

    friend class Node;

    public:
        bool insert(pair<int,int> point);
        vecPairInt searchQuery(pairInt begin,pairInt end);
        RangeTree() : mainTree(){};
        void getPDF(){
            this->mainTree.generatePDF();
        }

    protected:
        Node* searchFather(Node *&node, int key);
        void insertCoordinate(RangeTree *tree,pairInt point, bool coord);
        Node* updateYTree(Node* temp,pairInt point);
        void searchX(Node*& temp, int begin, int end, vecNode& nodesX);
        void search2D(Node*& temp, int beginX, int endX, int beginY, int endY, vecPairInt& points);
        void search1D(Node*& temp, int begin, int end, vecPairInt& points);

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
    auto temp = mainTree.root;
    auto searchNode =  mainTree.search(temp,point.first);
    if(searchNode!=NULL) return false;
    insertCoordinate(this,point,true);
    /* Node* current = mainTree.root;
    updateYTree(current, point); */
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

/* void RangeTree::searchX(Node*& temp, int begin, int end, vecNode& nodesX){
    if(!temp->right && !temp->left){
        if(temp->key >= begin && temp->key <= end)
            nodesX.push_back(temp);
    } else if(begin > temp->key && end > temp->key){
        searchX(temp->right,begin,end,nodesX);
    } else if(begin <= temp->key && end <= temp->key){
        searchX(temp->left, begin, end,nodesX);
    } else if(begin <= temp->key && end > temp->key){
        searchX(temp->left, begin, end,nodesX);
        searchX(temp->right, begin, end,nodesX);
    }
} */

void RangeTree::search1D(Node*& temp, int begin, int end, vecPairInt& points){
    if(!temp->right && !temp->left){
        if(temp->key >= begin && temp->key <= end)
            points.push_back(temp->point);
    } else if(begin > temp->key && end > temp->key){
        search1D(temp->right,begin,end,points);
    } else if(begin <= temp->key && end <= temp->key){
        search1D(temp->left, begin, end, points);
    } else if(begin <= temp->key && end > temp->key){
        search1D(temp->left, begin, end, points);
        search1D(temp->right, begin, end, points);
    }
}

void RangeTree::search2D(Node*& temp, int beginX, int endX, int beginY, int endY, vecPairInt& points){
    vecPairInt result;
    map<pairInt, int> counter;
    search1D(temp, beginX, endX, points);
    search1D(temp->YTree->mainTree.root, beginY, endY, points);
    for(int i = 0; i < points.size(); i++){
        if(counter.find(points[i]) != counter.end()) counter[points[i]]++;
        else counter.insert({points[i], 1});
    }

    for(auto it = counter.begin(); it != counter.end(); it++){
        if(it->second == 2) result.push_back(it->first);
    }
    points = result;
}

/* void RangeTree::search2D(Node*& temp, int beginX, int endX, int beginY, int endY, vecPairInt& points){
    vecNode nodesX;
    searchX(temp, beginX, endX, nodesX);
    for(int i=0; i<nodesX.size(); i++){
        if(nodesX[i]->YTree)
            search1D(nodesX[i]->YTree->mainTree.root, beginY, endY, points);
    }
} */

vecPairInt RangeTree::searchQuery(pairInt begin,pairInt end){
    vecPairInt points;
    Node* temp = mainTree.root;
    search1D(temp, begin.first, end.first, points); //busqueda 1D en X
    //search2D(temp, begin.first, end.first, begin.second, end.second, points);
    return points;
}



Node* RangeTree::updateYTree(Node* temp,pair<int,int> point){
    if(temp->right || temp->left){
        if (temp->left) updateYTree(temp->left,point);
        if(temp->right) updateYTree(temp->right,point);
        if(point.first > temp->key){
            updateYTree(temp->right,point);
        } else if(point.first <= temp->key){
            updateYTree(temp->left,point);
        }
        insertCoordinate(temp->YTree,point,false);
    }
    if(!temp->YTree){
        temp->YTree=new RangeTree;
        insertCoordinate(temp->YTree,temp->point,false); 
        return temp;
    }
    //insertCoordinate(temp->YTree,point,false);
    return temp;
}
