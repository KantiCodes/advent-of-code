#include <iostream>
#include<vector>

void printVector(const std::vector<std::vector<int>>& vec) {
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}