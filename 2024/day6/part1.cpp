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


struct NextMove
{
    unsigned long long i;
    unsigned long long j;
    char direction;

    // bool operator==(const NextMove& other) const {
    //     return i==other.i && j ==other.j && direction == other.direction;
    // }

    // Allow for adding to cout
    friend ostream& operator<<(ostream& os, const NextMove& move) {
        os << "(" << move.i << ", " << move.j << ") direction: " << move.direction;
        return os;
    }
    
};

NextMove finalMove = NextMove{-1, -1, END};


void printMove(NextMove move) {
    cout << "("<< move.i << "," << move.j <<")" << " direction:" << move.direction << " ";
}

bool isDirection(char direction) {
    return direction == UP || direction == DOWN || direction == RIGHT || direction == LEFT;
}

bool indexOutOfBounds(pair<unsigned long long, unsigned long long> id, vector<string> map) {
    // cout << "Checking index: " << id.first << " " << id.second << endl;
    // cout << "IMax: " << map.size() << " Jmax: " << map[0].length() << endl; 
    if (id.first == -1 || id.first == map.size()) {
        // cout << "111111";
        return true;
    }

    if (id.second == -1 || id.second == map[0].length()){
        // cout << "2222222";
        return true;
    }
    return false;
}


void getNextMove(NextMove& move, vector<string> map) {
    // cout << "Started at: ";
    // printMove(move);

    char current = move.direction;
    unsigned long long i = move.i;
    unsigned long long j = move.j;

    pair<unsigned long long, unsigned long long> nextRightId(i,j+1);
    pair<unsigned long long, unsigned long long> nextLeftId(i,j-1);
    pair<unsigned long long, unsigned long long> nextUpId(i-1,j);
    pair<unsigned long long, unsigned long long> nextDownId(i+1,j);

    pair<unsigned long long, unsigned long long> nextIndex;
    bool changedDirection;
    char nextDirection;
    char nextValue;

    switch (current)
    {
    case RIGHT:
        if (indexOutOfBounds(nextRightId, map)) {
            // cout << "Bad index" << endl;
            move.direction=END;
            return;
        }
        // cout << " [hit right] ";
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
        if (indexOutOfBounds(nextDownId, map)) {
            // cout << "Bad index" << endl;
            move.direction=END;
            return;
        }

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

        if (indexOutOfBounds(nextLeftId, map)) {
            // cout << "Bad index" << endl;
            move.direction=END;
            return;
        }
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
        if (indexOutOfBounds(nextUpId, map)) {
            // cout << "Bad index" << endl;
            move.direction=END;
            return;
        }
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
        throw exception();
    }

    // cout << " next value  was[" << nextValue << "] ";
    move.i = nextIndex.first;
    move.j=nextIndex.second;
    move.direction=nextDirection;
    // cout << "Finished at: ";
    // printMove(move);
    // cout << endl;
}


vector<string> makeMap(string fileName) {
    string input;
    char delimeter = '|';
    ifstream rulesFile(fileName);
    vector<string> map;

    while(getline(rulesFile, input)) {
        map.push_back(input);
    }
    cout << "Made map "<<endl;
    return map;
}

NextMove findStartngMove(vector<string> map){
    unsigned long long ii,jj;
    char startingDirection;
    bool shouldBreak=false;
    // cout << " SB: " << shouldBreak << endl;

    // cout << "Map I size: " << map.size() << " Map J size:" << map[0].length() << endl;

    for (unsigned long long i=0; i<map.size(); i++) {
        // cout << "i :" << i << endl;
        for (unsigned long long j=0; j<map[i].length(); j++) {
            // cout << "j :" << j << endl;
            startingDirection = map[i][j];
            // cout << "Current direction: " << startingDirection << endl;
            if (isDirection(startingDirection)) {
                ii=i;
                jj=j;
                shouldBreak = true;
                break;
            }
        }
        if (shouldBreak) break;
    }
    // cout << "ii: " << ii << " jj: " << jj << " starting diretion" << startingDirection << endl;

    return NextMove{ii,jj, startingDirection};

}

bool isGameDeadlocked(const vector<string>& map, NextMove move) {
    set<tuple<unsigned long long,unsigned long long,char>> seen;
    do {
        if (seen.find(tuple(move.i, move.j, move.direction)) != seen.end()) {
            cout << "This move is deadlocked: ";
            printMove(move);
            cout << endl;
            return true;
        }
        seen.insert(tuple(move.i, move.j, move.direction));
        getNextMove(move, map);
        
    } while (move.direction != END);
    return false;
}


int main (int argc, char* argv[]) {
    string filePath =argv[1];
    cout << "Running file: " << argv[1] << endl;
    auto map = makeMap(filePath);

    NextMove firstMoveOriginal = findStartngMove(map);
    NextMove firstMove = firstMoveOriginal;

    set<pair<unsigned long long,unsigned long long>> seen;
    seen.insert(pair<unsigned long long, unsigned long long>(firstMoveOriginal.i, firstMoveOriginal.j));
    NextMove nextMove = findStartngMove(map);
    do {
        getNextMove(nextMove, map);
        seen.insert(pair<unsigned long long, unsigned long long>(nextMove.i, nextMove.j));
        

    } while (nextMove.direction != END);
    cout << "Game one result: " << seen.size() << endl;

    unsigned long long part2Result = 0;
    // Part two faster
    for (auto move: seen) {
        // cout << move.first << " " << move.second << endl;
        unsigned long long i = move.first;
        unsigned long long j = move.second;

        if (i==firstMoveOriginal.i && j==firstMoveOriginal.j) {
            continue;
        }
        char currentChar = map[i][j];
        if (currentChar == BLOCK) {
            continue;
        }
        cout << "Game for " << "(" <<i << "," << j <<endl;
        auto mapCopy = map;
        mapCopy[i][j] = '#';

        if (isGameDeadlocked(mapCopy, firstMoveOriginal)) {
            part2Result ++;
            cout << "is bad" << endl;
        }
        else cout << "is good" << endl;
    }
    


    // //Part two
    // unsigned long long part2Result = 0;
    // for (unsigned long long i=0; i<map.size(); i++) {
    //     cout << "i :" << i << " ";
    //     for (unsigned long long j=0; j<map[0].length(); j++) {
    //         cout << " j " << j;
    //         if (i==firstMoveOriginal.i && j==firstMoveOriginal.j) {
    //             continue;
    //         }
            
    //         char currentChar = map[i][j];
    //         if (currentChar == BLOCK) {
    //             continue;
    //         }

    //         auto mapCopy = map;
    //         mapCopy[i][j] = '#';
    //         // cout << "Starting a new game: " << i << " " << j << endl;
    //         if (isGameDeadlocked(mapCopy, firstMoveOriginal)) {
    //             part2Result ++;
    //         }

            
    //     }
    //     cout << endl;
    // }

    cout << "Part2: " << part2Result;




}