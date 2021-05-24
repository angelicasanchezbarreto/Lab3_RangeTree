#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<pair<int,int>> read_file(string name){
    fstream file(name);
    vector<pair<int,int>> result;
    vector<int> row;
    string line, num1, num2;
    while(getline(file, line)){
        stringstream s1(line);
        while(s1 >> num1 >> num2){
            pair<int, int> temporal{stoi(num1), stoi(num2)};
            result.push_back(temporal); 
        }
    }

    return result;
}

void write_file(string name, vector<pair<int, int>> points){
    fstream file;
    file.open(name, ios::out);
    for(int i = 0; i < points.size(); i++){
        file << points[i].first << " " << points[i].second << endl;
    }   
    file.close();
}