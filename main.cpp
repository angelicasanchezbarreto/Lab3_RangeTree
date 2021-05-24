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
    /* rangeTree.insert(make_pair(6,10));
    rangeTree.insert(make_pair(17,10));
    rangeTree.insert(make_pair(20,10));
    rangeTree.insert(make_pair(15,10));
    rangeTree.insert(make_pair(5,10));
    rangeTree.insert(make_pair(4,10)); */

    vecPairInt points = read_file("files/points.txt");

    for(int i=2; i<points.size(); i++){
        rangeTree.insert(points[i]);
    }

    vecPairInt query = rangeTree.searchQuery(points[0],points[1]);
    write_file("files/result.txt", query);

    for(auto i:query)
        cout << "[" << i.first << "," << i.second << "]" << endl;

    
    return 0;
}
