#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <fstream>
#include <vector>
using namespace std;

template <typename KeyType, typename ValueType>
void printMap(const std::unordered_map<KeyType, std::set<ValueType>>& rules) {
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



int main () {

    string input;
    char delimeter = '|';
    unordered_map<string, set<string>> rules;
    ifstream rulesFile("2024/day5/rules_big.in");

    while(getline(rulesFile, input)) {
        int delimeterPos = input.find(delimeter);
        string keyStr = input.substr(0, delimeterPos);
        string valueStr = input.substr(delimeterPos+1, input.size());

        cout << keyStr << " " << valueStr << endl;

        rules[keyStr].insert(valueStr);

    }

    printMap(rules);

    ifstream lineFile("2024/day5/lines_big.in");
    int output = 0;
    
    while(std::getline(lineFile, input)) {
        cout << "Working on line: " << input << endl;
        stringstream lineStream(input);
        string currentValStr;
        unordered_map<string, bool>seenMap;
        bool good = true;
        vector<int>values;
        while (getline(lineStream, currentValStr, ',')){
            cout << "currentValStr: " << currentValStr << endl;
            values.push_back(stoi(currentValStr));
        }

        d

    }

    cout << "Output: " << output;

    return output;
}