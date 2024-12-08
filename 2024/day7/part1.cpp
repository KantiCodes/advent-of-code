#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <fstream>
#include <vector>
#include <functional>
#include <cassert>
#include <cmath>



using namespace std;

const char LEFT = '<';
const char RIGHT = '>';
const char DOWN = 'v';
const char UP = '^';
const char FREE = '.';
const char BLOCK = '#';
const char END = 'e';

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& point) {
    os << "(" << point.first << ", " << point.second << ")";
    return os;
}

template <typename Iterable>
void printVector(const Iterable& v) {
    for (const auto& vv: v) {
        cout <<"["<< vv <<"] " << endl;
    }
    cout << endl;
}

vector<string> makeLines(string fileName) {
    string input;
    unsigned long long value;
    ifstream inputFile(fileName);
    vector<string> lines;


    while(getline(inputFile, input)) {
        
        lines.push_back(input);
    }
    return lines;
}

int getSize(unsigned lon) {
    int digits = 0;
    while (lon != 0) {
        digits ++;
        lon /= 10;
    }
    return digits;
}

void generateCombinations(string current, unsigned long long n, vector<string>& results) {
    string options = "*+|";

    if (current.length() == n){
        results.push_back(current);
        return;
    }

    for (auto c: options) {
        generateCombinations(current+c, n, results);
    }
};

void printPoint(pair<int,int>p){
    cout << "(" << p.first << "," << p.second << ")";
}

bool isPointWithinBounds(pair<int, int>p, const vector<string>& map) {
    int x=p.first;
    int y=p.second;

    return (
        x>=0 && x <map.size() &&
        y>=0 && y< map[0].size()
    );
}


int main (int argc, char* argv[]) {

    string filePath =argv[1];
    cout << "Running file: " << argv[1] << endl;
    auto lines = makeLines(filePath);
    printVector(lines);
    
    unordered_map<char, vector<pair<int, int>>> antenas;

    for (int i=0; i<lines.size(); i++) {
        for (int j=0; j<lines[0].size(); j++) {

            char c = lines[i][j];
            if (c != '.') {
                antenas[c].push_back(pair(i,j));
            }
        }
    }

    for (auto pair:antenas) {
        cout << pair.first << ": ";
        for (auto xySet:pair.second) {
            cout << "(" << xySet.first << "," << xySet.second  << ") ";
        }
 
    }
    cout << endl;
    int result =0;
    set<pair<int,int>> goods;

    for (auto signAndCoords:antenas) {
        char antenaSign = signAndCoords.first;
        vector<pair<int,int>> cords = signAndCoords.second;
        cout << "Going over antena sign: " << antenaSign << endl;



        for (int i=0; i<cords.size(); i++) {
            pair<int, int> firstPoint = cords[i]; 
            for (int j=i+1; j<cords.size(); j++) {

                pair<int, int> secondPoint = cords[j];
                pair<int, int>newFirst = firstPoint;
                pair<int, int> newSecond = secondPoint;
                std::cout << "testing(" << firstPoint.first << "," << firstPoint.second << ") with(" << secondPoint.first << ", " << secondPoint.second << ")" << std::endl;

                if (firstPoint.first < secondPoint.first) {
                    newFirst.first -= abs(firstPoint.first-secondPoint.first);
                    newSecond.first += abs(firstPoint.first-secondPoint.first);
                }
                else {
                    newFirst.first += abs(firstPoint.first-secondPoint.first);
                    newSecond.first -= abs(firstPoint.first-secondPoint.first);

                }

                if (firstPoint.second < secondPoint.second) {
                    newFirst.second -= abs(firstPoint.second - secondPoint.second);
                    newSecond.second += abs(firstPoint.second - secondPoint.second);
                }
                else {
                    newFirst.second += abs(firstPoint.second - secondPoint.second);
                    newSecond.second -= abs(firstPoint.second - secondPoint.second);
                }

                if (isPointWithinBounds(newFirst, lines)){
                    goods.insert(newFirst);
                    cout << "Good point 1:";
                    printPoint(newFirst);
                }
                if (isPointWithinBounds(newSecond, lines)) {
                    cout << " Good point 2:";
                    printPoint(newSecond);
                    goods.insert(newSecond);
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    // int result = goo
    cout << "Result: " << goods.size() << endl;

    printVector(goods);
    
}