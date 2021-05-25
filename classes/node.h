#ifndef AVLTREE_NODE_H
#define AVLTREE_NODE_H

#include <utility>
#include <fstream>

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

    RangeTree *YTree;

    Node() : left(nullptr), right(nullptr),YTree(nullptr){};
    
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
        this->YTree = nullptr;
    };

    Node(Node *node){
        this->height=node->height;
        this->key=node->key;
        this->left=node->left;
        this->right=node->right;
        this->point=node->point;
    }

    void printNodesConexiones(fstream &file){
		if(this->left != nullptr){
			file << "\"" << this << "\"->";
			file << "\"" << left << "\";\n"; 
			this->left->printNodesConexiones(file);
		}
		if(this->right != nullptr){
			file << "\"" << this << "\"->";
			file << "\"" << right << "\";\n"; 
			this->right->printNodesConexiones(file);
		}
	}
	void printAllNodes(fstream &file){
		file << "\"" << this << "\" [\n";
		file << "\tlabel = \"" << this->key <<"\\n grado: "<<this->height << " \"\n]\n";
		if(this->left != nullptr){
			this->left->printAllNodes(file);
		}
		if(this->right != nullptr){
			this->right->printAllNodes(file);
		}
	}

};

#endif //AVLTREE_NODE_H
