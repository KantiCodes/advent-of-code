#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <sstream>

#include <iostream>
#include<vector>
#include <cassert>
#include <utility>

std::string xmas = "XMAS";

void printVectorFlat(const std::vector<char>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
}

void printVector(const std::vector<std::vector<char>>& vec) {
    std::cout<<"*****************************************" <<std::endl;
    for (const auto& row : vec) {
        printVectorFlat(row);
        std::cout << std::endl;
    }
    std::cout<<"*****************************************" << std::endl;
}

bool ok(std::vector<std::vector<char>> vec, int i, int j){
    std::pair<int,int> m1Index(i,j);
    std::pair<int,int> s1Index(i,j+2);
    std::pair<int,int> a1Index(i+1,i+1);
    std::pair<int,int> m2Index(i+2,j);
    std::pair<int,int> s2Index(i+2,j+2);

    std::cout << "Value at m1Index (" << m1Index.first << ", " << m1Index.second 
          << "): " << vec[m1Index.first][m1Index.second] << std::endl;

std::cout << "Value at s1Index (" << s1Index.first << ", " << s1Index.second 
          << "): " << vec[s1Index.first][s1Index.second] << std::endl;

std::cout << "Value at a1Index (" << a1Index.first << ", " << a1Index.second 
          << "): " << vec[a1Index.first][a1Index.second] << std::endl;

std::cout << "Value at m2Index (" << m2Index.first << ", " << m2Index.second 
          << "): " << vec[m2Index.first][m2Index.second] << std::endl;

std::cout << "Value at s2Index (" << s2Index.first << ", " << s2Index.second 
          << "): " << vec[s2Index.first][s2Index.second] << std::endl;

    return (
        vec[m1Index.first][m1Index.second] == 'M' &&
        vec[s1Index.first][s1Index.second] == 'S' &&
        vec[a1Index.first][a1Index.second] == 'A' &&
        vec[m2Index.first][m2Index.second] == 'M' &&
        vec[s2Index.first][s2Index.second] == 'S'

    );
}

int solutionMasMatrix(std::vector<std::vector<char>> vec) {
    int result=0;
    for (int i=0; i<vec.size()-2; i++){
        for(int j=0; j<vec[0].size()-2; j++) {
            if(ok(vec,i,j)){
                std::cout<<"hit for: " << i << " " << j << std::endl;
                result ++;
            }
            else {
                std::cout << "Not ok" << std::endl;
            }   
        }
    }
    return result;
}


int horizontalSolve(std::vector<char> line) {
    int matchCount = 0;
    int result = 0;

    for (int j =0; j<line.size(); j++) {
        char currentValue = line[j];
        char expectedValue = xmas[matchCount];
        // std::cout<< "currentValue: " << currentValue << " expectedValue: " << expectedValue << std::endl;

        // If the current value is not a match we go back to the beginning of XMAS
        if (currentValue != expectedValue) {
            matchCount = 0;
        }

        // If current character is equal to the next expected character
        if (currentValue == xmas[matchCount]) {
            matchCount++;
        }
        
        // Full word was matched
        if (matchCount==4) {
            result+=1;
            matchCount=0;
        }
        // std::cout << "matchCount: " << matchCount << std::endl;
    }

    return result;
}


void rotateMatrix(std::vector<std::vector<char>>& matrix) {
    int n = matrix.size();

    // Step 1: Transpose the matrix
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }

    // Step 2: Reverse each row
    for (int i = 0; i < n; ++i) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

int diagnonal(std::vector<std::vector<char>>vec){
    int output=0;
    bool firstLoop = true;
    for (int r=0; r<vec.size() && vec.size() -r >= 4; r++) {
        for (int r_pos_start=0; r_pos_start<vec[r].size()  && vec[0].size()-r_pos_start >= 4; r_pos_start++){
            int matchCount = 0;
            for (int j=0; j<vec[r].size()-r_pos_start && j<vec.size()-r; j++) {
                auto current = vec[r+j][r_pos_start+j];
                auto expected = xmas[matchCount];

                // std::cout<< "currentValue: " << current << " expectedValue: " << expected << std::endl;

                // If the current value is not a match we go back to the beginning of XMAS
                if (current != expected) {
                    matchCount = 0;
                }

                // If current character is equal to the next expected character
                if (current == xmas[matchCount]) {
                    matchCount++;
                }
                
                // Full word was matched
                if (matchCount==4) {
                    // std::cout << "FOUND!" << std::endl;
                    output+=1;
                    matchCount=0;
                }
                // std::cout << "matchCount: " << matchCount << std::endl;

            }
            std::cout<<std::endl;
            if (!firstLoop) {
                break;
            }
        }
        firstLoop = false;
    }
    return output;
}



// Time complexity: O(n*m) -> `n` is number of lines, `m` is the line length
// Space complexit: O(n)
int inplace(){
    std::string input;
    std::vector<std::vector<char>> vv;

    int output=0;
    char curr;
    bool isLineGood;
    int directionSide, distance;

    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        std::vector<char>tmp;


        // Line is good unless proven wrong
        isLineGood = true;
        directionSide = 0;

        // If one value then always good
        if (input.length() <= 1) {
            output+=1;
            continue;
        }
        while(iss >> curr) {
            std::cout << "curr: " << curr << std::endl;
            tmp.push_back(curr);
        }
        vv.push_back(tmp);

    }
    
    printVector(vv);

    auto vvHorizontallyReversed = vv;
    auto vvVerticallyReversed = vv;
    auto vvBothReversed = vv;

    for (auto& v: vvHorizontallyReversed) {
        reverse(v.begin(), v.end());
    }
    reverse(vvVerticallyReversed.begin(), vvVerticallyReversed.end());
    reverse(vvBothReversed.begin(), vvBothReversed.end());
    for (auto& v: vvBothReversed) {
        reverse(v.begin(), v.end());
    }
    

    std::cout <<"Vertically reversed: " << std::endl;
    printVector(vvVerticallyReversed);
    std::cout <<"Horizontally reversed: " << std::endl;
    printVector(vvHorizontallyReversed);
    std::cout <<"vvBothReversed reversed: " << std::endl;
    printVector(vvBothReversed);


    int rows = vv.size();
    int columns = vv[0].size();

    // std::cout << "Vector 1: " << vv[0];

    int outputHorizontal=0;
    int outputHorizontalBackwards=0;
    int outputVertical=0;
    int outputVerticalBackwards=0;


    // horizontal
    for (int i =0; i<rows; i++) {
        std::vector currentLine = vv[i];
        std::vector<char> currentLineBackwards = currentLine;
        reverse(currentLineBackwards.begin(), currentLineBackwards.end());
    
        std::cout << "Current line: " << std::endl;
        printVectorFlat(currentLine);
        std::cout <<std::endl << "Current line backwards: " << std::endl;
        printVectorFlat(currentLineBackwards);
        std::cout << std::endl;

        outputHorizontal += horizontalSolve(currentLine);
        outputHorizontalBackwards += horizontalSolve(currentLineBackwards);
    }


    // Vertical
    std::vector<std::vector<char>> vvRotatedP90 = vv;
    rotateMatrix(vvRotatedP90);
    for (int i =0; i<vvRotatedP90.size(); i++) {
        std::vector verticalLine = vvRotatedP90[i];
        std::vector verticalLineBackwards = verticalLine;
        std::reverse(verticalLineBackwards.begin(), verticalLineBackwards.end());
        outputVertical +=  horizontalSolve(verticalLine);
        outputVerticalBackwards +=  horizontalSolve(verticalLineBackwards);
    }

    // assert (outputVertical == 2);
    // assert (outputVerticalBackwards == 1);


    // Diagnonal
    std::cout<<"*******************Diagnonal********************" << std::endl;
    int outputDiagonalTopLeftBottomRight = diagnonal(vv);
    int outputDiagonalTopRightBottomLeft = diagnonal(vvHorizontallyReversed);
    int outputDiagonalBottomLeftTopRight = diagnonal(vvVerticallyReversed);
    int outputDiagonalvvBothReversed = diagnonal(vvBothReversed);


    std::cout << "outputHorizontal: " << outputHorizontal << std::endl;
    std::cout << "outputHorizontalBackwards: " << outputHorizontalBackwards << std::endl;

    std::cout << "outputVertical:" << outputVertical << std::endl;
    std::cout << "outputVerticalBackwards:" << outputVerticalBackwards << std::endl;


    std::cout << "outputDiagonalTopLeftBottomRight: " << outputDiagonalTopLeftBottomRight << std::endl;
    std::cout << "outputDiagonalTopRightBottomLeft: " << outputDiagonalTopRightBottomLeft << std::endl;
    std::cout << "outputDiagonalBottomLeftTopRight: " << outputDiagonalBottomLeftTopRight << std::endl;
    std::cout << "outputDiagonalvvBothReversed: " << outputDiagonalvvBothReversed << std::endl;
    // assert (outputDiagonalTopLeftBottomRight==1);

    std::cout << "Total: " << outputHorizontal+outputHorizontalBackwards +outputVertical + outputVerticalBackwards + outputDiagonalTopLeftBottomRight+outputDiagonalTopRightBottomLeft+outputDiagonalBottomLeftTopRight+outputDiagonalvvBothReversed << std::endl;

    std::cout<<"Mas matrix: " << solutionMasMatrix(vv) + solutionMasMatrix(vvVerticallyReversed) + solutionMasMatrix(vvHorizontallyReversed) + solutionMasMatrix(vvBothReversed);

    return output;
}


int main() {
    int output = inplace();
    // std::cout << "Value: " << output << std::endl;
    return 0;
}