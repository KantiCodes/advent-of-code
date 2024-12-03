#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <sstream>

// Time complexity: O(n*m) -> `n` is number of lines, `m` is the line length
// Space complexit: O(n)
int inplace() {
    std::string input;
    std::vector<int> ll;
    int output=0;
    int prev, curr;
    bool isLineGood;
    int directionSide, distance;

    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);

        // Line is good unless proven wrong
        isLineGood = true;
        directionSide = 0;

        // If one value then always good
        if (input.length() <= 1) {
            output+=1;
            continue;
        }

        // Load the first item off the stream
        iss >> prev;

        while(iss >> curr) {
            std:: cout << "Current: " << curr << " Prev: " << prev << std::endl;
            distance = curr - prev;

            // Check distance out of bounds
            if (abs(distance) < 1 || abs(distance) > 3) {
                std::cout << "One: " << distance;
                isLineGood = false;
                break;
            }
            
            // if side already established
            if (directionSide != 0) {
                
                // if side negative but values increase
                if (directionSide == -1 && curr > prev) {
                    isLineGood = false;
                    break;
                }
                // if side positive but values decrease
                if (directionSide == 1 && curr < prev) {
                    isLineGood = false;
                    break;
                }

            }

            directionSide = (distance < 0) ? -1: 1;
            prev = curr;

        }

        if (isLineGood) {
            output +=1;
            std::cout << "Safe" << std::endl;
        }
        else {
            std::cout << "Not Safe" << std::endl;
        }
    }
    return output;

}


int main() {
    int output = inplace();
    std::cout << "Value: " << output << std::endl;
    return 0;
}