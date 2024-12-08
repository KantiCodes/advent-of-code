// #include <string>
// #include <iostream>
// #include <sstream>
// #include <unordered_map>
// #include <set>
// #include <fstream>
// #include <vector>
// #include <functional>
// #include "part1.cpp"
// #include "/home/bartek/Projects/advent-of-code/utils.cpp";
// using namespace std;


// bool isGameDeadlocked(vector<string> map, NextMove move) {
//     set<tuple<int,int,char>> seen;
//     bool isDeadlocked = false;
//     do {
//         if (seen.find(tuple(move.i, move.j, move.direction)) != seen.end()) {
//             cout << "Already been at: ";
//             printMove(move);
//             isDeadlocked = true;
//             break;
//         }
//         seen.insert(tuple(move.i, move.j, move.direction));
//         getNextMove(move, map);
        
//     } while (move.direction != END);

//     return isDeadlocked;
// }

// int main (int argc, char* argv[]) {
//     string filePath =argv[1];
//     cout << "Running file: " << argv[1] << endl;
//     assert(filePath == "2024/day6/small.in" || filePath == "2024/day6/big.in") ;
//     auto map = makeMap("2024/day6/small.in");
//     // }
//     printVector(map);
//     bool isDeadlocked = isGameDeadlocked(map);
//     cout << "The game deadlock =" << isDeadlocked << endl;
// }