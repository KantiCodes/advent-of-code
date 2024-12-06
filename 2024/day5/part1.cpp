#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <fstream>
#include <vector>
#include <functional>
using namespace std;

unordered_map<int, set<int>> rules;


// It should return true if the first argument should come before the second; otherwise, it should return false.
bool sortFunc(int i, int j) {
    auto iRules = rules[i];
    if (iRules.find(j) != iRules.end()){
        return true;
    }
    return false;
}

template <typename Iterable>
void printVector(const Iterable& v) {
    for (const auto& vv: v) {
        cout <<"["<< vv <<"] ";
    }
    cout << endl;
}

template <typename KeyType, typename ValueType>
void printMap(const std::unordered_map<KeyType, std::set<ValueType>>& rules) {
    cout << "Rules: " << endl;
    for (const auto& [key, values] : rules) {
        std::cout << key << ": {";
        for (auto it = values.begin(); it != values.end(); ++it) {
            std::cout << *it;
            if (std::next(it) != values.end()) {
                std::cout << ", ";
            }
        }
        std::cout << "}" << std::endl;
    }
}

void printSeenMap(unordered_map<int,bool> seenMap) {
    cout << "seenMap: ";
    for (auto [key, values] : seenMap) {
        cout << key << ": " << values;
    }
    cout << endl;
}


// while (getline(lineStream, currentValStr, ','))

bool checkIfGood(vector<int>vec) {
    unordered_map<int, bool>seenMap;
    // printSeenMap(seenMap);
    // cout << "Working on the line:";
    // printVector(vec);
    for (int v:vec) {
        // cout << "Running for V: " << v << endl;;
        // printSeenMap(seenMap);
        seenMap[v] = true;
            for (auto notAllowedBefore: rules[v]) {
                if (seenMap[notAllowedBefore] == true) {
                    // cout << "Fail" << endl;
                    return false;
                }
            }
    }
    cout << "Success" << endl;
    return true;
}

bool checkIfBad(vector<int>vec) {
    return !checkIfGood(vec);
}


void makeRules(string fileName) {
    string input;
    char delimeter = '|';
    ifstream rulesFile(fileName);

    while(getline(rulesFile, input)) {
        int delimeterPos = input.find(delimeter);
        string keyStr = input.substr(0, delimeterPos);
        string valueStr = input.substr(delimeterPos+1, input.size());

        // cout << keyStr << " " << valueStr << endl;

        rules[stoi(keyStr)].insert(stoi(valueStr));

    }
}

int main () {
    makeRules("2024/day5/rules_big.in");
    printMap(rules);

    ifstream allLinesFile("2024/day5/lines_big.in");
    string input;
    vector<vector<int>>allLines;
    int output = 0;

    while(getline(allLinesFile, input)) {
        stringstream currentLineStream(input);
        string currentValStr;
        vector<int> currentLine;
        string vStr;
        while(getline(currentLineStream, vStr, ',')){
            currentLine.push_back(stoi(vStr));
        }
        allLines.push_back(currentLine);

    }
    vector<vector<int>> allGoodLines; 
    vector<vector<int>> allBadLines; 
    copy_if(allLines.begin(), allLines.end(), back_inserter(allGoodLines), checkIfGood);

    cout << "Good lines: " << endl;
    for (auto v: allGoodLines) {
        printVector(v);
    }

    copy_if(allLines.begin(), allLines.end(), back_inserter(allBadLines), checkIfBad);
    cout << "Bad lines: " << endl;
    for (auto v: allBadLines) {
        printVector(v);
    }

    for (auto line: allGoodLines) {
        int middleElement = (line[line.size()/2]);
        cout << "middleElement: " << middleElement << endl;
        output += middleElement;
    }



    int badOutput = 0;

    cout << "allBadLines: " << allBadLines.size() << endl;
    int count = 0;

    for (auto line: allBadLines) {
        cout << "Line before fixing: ";
        printVector(line);
        sort(line.begin(), line.end(), sortFunc);
        cout << "Line after sorting: ";
        printVector(line);
        badOutput += line[line.size()/2];
       
    }

    cout << "output: " << output << endl;
    cout << "badOutput:" << badOutput << endl;
        
    return output;
}