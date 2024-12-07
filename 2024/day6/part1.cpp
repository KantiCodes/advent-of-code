#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <fstream>
#include <vector>
#include <functional>
using namespace std;

vector<string> map;
const char LEFT = '<';
const char RIGHT = '>';
const char DOWN = 'v';
const char UP = '^';
const char FREE = '.';
const char BLOCK = '#';
const char END = 'e';

struct NextMove
{
    int i;
    int j;
    char direction;
};


void printMove(NextMove move) {
    cout << "("<< move.i << "," << move.j <<")" << " direction:" << move.direction << " ";
}

bool isDirection(char direction) {
    return direction == UP || direction == DOWN || direction == RIGHT || direction == LEFT;
}

const char directionChange(const char current) {
    switch (current)
    {
    case UP:
        return RIGHT;
    case RIGHT:
        return DOWN;
    case DOWN:
        return LEFT;
    case LEFT:
        return UP;
    
    default:
        3/0;
        break;
    }
}

bool indexOutOfBounds(pair<int, int> id) {
    // cout << "Checking index: " << id.first << " " << id.second << endl;
    // cout << "IMax: " << map.size() << " Jmax: " << map[0].length() << endl; 
    if (id.first < 0 || id.first >= map.size()) {
        cout << "111111";
        return true;
    }

    if (id.second < 0 || id.second >= map[0].length()){
        cout << "2222222";
        return true;
    }
    return false;
}


void getNextMove(NextMove& move) {
    cout << "Started at: ";
    printMove(move);

    char current = move.direction;
    int i = move.i;
    int j = move.j;

    pair<int, int> nextRightId(i,j+1);
    pair<int, int> nextLeftId(i,j-1);
    pair<int, int> nextUpId(i-1,j);
    pair<int, int> nextDownId(i+1,j);

    pair<int, int> nextIndex;
    bool changedDirection;
    char nextDirection;
    char nextValue;

    switch (current)
    {
    case RIGHT:
        cout << " [hit right] ";
        nextValue = map[nextRightId.first][nextRightId.second];
        // If right is blocked then turn to down
        if (nextValue == BLOCK) {
            nextIndex = nextDownId;
            nextDirection = DOWN;
        }
        else {
            nextIndex = nextRightId;
            nextDirection = RIGHT;
        }
        break;
    case DOWN:
        nextValue = map[nextDownId.first][nextDownId.second];
        // If down is blocked then turn to left
        if (nextValue == BLOCK) {
            nextIndex = nextLeftId;
            nextDirection = LEFT;
        }
        else {
            nextIndex = nextDownId;
            nextDirection = DOWN;
        }
        break;
    case LEFT:
        nextValue = map[nextLeftId.first][nextLeftId.second];
        // If left is blocked then turn to left
        if (nextValue == BLOCK) {
            nextIndex = nextUpId;
            nextDirection = UP;
        }
        else {
            nextIndex = nextLeftId;
            nextDirection = LEFT;
        }
        break;
    case UP:
        nextValue = map[nextUpId.first][nextUpId.second];
        // If up is blocked then turn to right
        if (nextValue == BLOCK) {
            nextIndex = nextRightId;
            nextDirection = RIGHT;
        }
        else {
            nextIndex = nextUpId;
            nextDirection = UP;
        }
        break;
    default:
        int a = 3/0;
    }
    if (indexOutOfBounds(nextIndex)) {
        cout << "Bad index" << endl;
        nextDirection = END;
    }
    cout << " next value  was[" << nextValue << "] ";
    move.i = nextIndex.first;
    move.j=nextIndex.second;
    move.direction=nextDirection;
    cout << "Finished at: ";
    printMove(move);
    cout << endl;
}


vector<string> makeMap(string fileName) {
    string input;
    char delimeter = '|';
    ifstream rulesFile(fileName);

    while(getline(rulesFile, input)) {
        map.push_back(input);
    }
    return map;
}

int main () {
    string input;

    // if (input == "small") {
    // auto map = makeMap("2024/day6/small.in");
    // }
    // else {
    auto map = makeMap("2024/day6/big.in");
    // }

    int ii,jj;
    char startingDirection;
    bool shouldBreak;
    for (int i=0; i<map.size(); i++) {
        for (int j=0; j<map[i].length(); j++) {
            startingDirection = map[i][j];
            if (isDirection(startingDirection)) {
                ii=i;
                jj=j;
                shouldBreak = true;
                break;
            }
        }
        if (shouldBreak) break;
    }
    int output = 0;
    set<pair<int,int>> seen;
    NextMove nextMove{ii,jj,startingDirection};
    do {
        seen.insert(pair<int, int>(nextMove.i, nextMove.j));
        getNextMove(nextMove);
        

    } while (nextMove.direction != END);
    cout << seen.size();
}