#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

// Time complexity: O(n*log n)
// Space complexit: O(n)
int sort_based() {
    std::string input;
    int l,r;
    std::unordered_map<int,int> ll, rr;
    int output=0;

    while (std::cin >> l >> r) {
        ll[l] += 1;
        rr[r] += 1;
    }

    for (const std::pair<int, int> key_value: ll) {
        int key = key_value.first;
        int value = key_value.second;
        output += key * value * rr[key];

    }
    std::cout << output;
    return output;
}


int main() {
    
    return sort_based();
}