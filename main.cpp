#include <iostream>
#include <vector>
#include <algorithm>
#include "classes/avltree.h"
#include "classes/rangetree.h"
#include "file.h"

using namespace std;

int main() {
    RangeTree rangeTree;

    //EJEMPLO DEL PROFE DONDE NECESITABA MODIFICACIÓN
    /* rangeTree.insert(make_pair(6,23));
    rangeTree.insert(make_pair(17,16));
    rangeTree.insert(make_pair(20,85));
    rangeTree.insert(make_pair(15,35));
    rangeTree.insert(make_pair(5,11));
    rangeTree.insert(make_pair(4,9));

    vecPairInt query = rangeTree.searchQuery(make_pair(6,13),make_pair(18,50));
    write_file("files/result.txt", query);
    //for(auto i:query)
    //    cout << "[" << i.first << "," << i.second << "]" << endl;
    rangeTree.getPDF(); */


    RangeTree rangeTree2;
    vecPairInt points = read_file("files/dataset100.txt");
    for(int i=2; i<points.size(); i++){
        rangeTree2.insert(points[i]);
    }
    vecPairInt query1 = rangeTree2.searchQuery(points[0],points[1]);
    write_file("files/result100.txt", query1);
    //rangeTree2.getPDF();
    
    return 0;
}
