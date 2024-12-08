#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <fstream>
#include <vector>
#include <functional>
#include <cassert>

using namespace std;

const char LEFT = '<';
const char RIGHT = '>';
const char DOWN = 'v';
const char UP = '^';
const char FREE = '.';
const char BLOCK = '#';
const char END = 'e';

template <typename Iterable>
void printVector(const Iterable& v) {
    for (const auto& vv: v) {
        cout <<"["<< vv <<"] ";
    }
    cout << endl;
}

struct Line {
    unsigned long long target;
    vector<unsigned long long> values;

    // Method to return a printable string of the `values` vector
    string getPrintableValue() const {
        string s = "[";
        for (size_t i = 0; i < values.size(); ++i) {
            s += to_string(values[i]);
            if (i != values.size() - 1) {
                s += ", ";
            }
        }
        s += "]";
        return s;
    }

    // Friend function to overload <<
    friend ostream& operator<<(ostream& os, const Line& line) {
        os << "Line(target=" << line.target << ", values=" << line.getPrintableValue() << ")";
        return os;
    }
};

vector<Line> makeLines(string fileName) {
    string input;
    unsigned long long value;
    ifstream inputFile(fileName);
    vector<Line> lines;

    while(getline(inputFile, input)) {
        vector<unsigned long long> numbers;
        
        int colonPos = input.find(':');
        istringstream iss(input.substr(colonPos+1));
        string leftSubStr = input.substr(0, colonPos);
        cout << "Left substr: " << leftSubStr << endl;
        unsigned long long leftVal = stoul(leftSubStr);
        
        while(iss >> value){
            numbers.push_back(value);
        }
        Line line{leftVal, numbers};
        lines.push_back(line);
    }
    return lines;
}

void generateCombinations(string current, int n, vector<string>& results) {
    string options = "*+";

    if (current.length() == n){
        results.push_back(current);
        return;
    }

    for (auto c: options) {
        generateCombinations(current+c, n, results);
    }
}


int main (int argc, char* argv[]) {

    string filePath =argv[1];
    cout << "Running file: " << argv[1] << endl;
    auto lines = makeLines(filePath);
    printVector(lines);
    unsigned long long output = 0;

    // vector<char> operSet;

    for (auto line: lines) {
        int spaces = line.values.size() - 1;
        cout << "Working a line: " << line << "With spaces: " << spaces << endl;
        if (spaces == 0 && line.target == line.values[0]) {
            output += line.target;
        }
            else {
                vector<string> possibilities;
                generateCombinations("", spaces, possibilities);
                cout << "All possibilities: ";
                printVector(possibilities);
                for (string instructionLine:possibilities){
                    unsigned long long result = line.values[0];
                    for (int i=0; i<spaces; i++){
                        unsigned long long currentValue = line.values[i+1];
                        if (instructionLine[i] == '*') {
                            result *= currentValue;
                        }
                        else {
                            result += currentValue;
                        }
                    }
                    if (result == line.target) {
                        output += line.target;
                        cout << "Worked combination: " << instructionLine;
                        break;
                    }
                }
            }
    }
    cout << "Output: " << output;
}