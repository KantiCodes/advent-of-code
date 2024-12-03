#include <iostream>
#include <vector>
#include <algorithm>

// Time complexity: O(n*log n)
// Space complexit: O(n)
int sort_based() {
    std::string input;
    int l,r;
    std::vector<int> ll, rr;
    int output=0;

    while (std::cin >> l >> r) {
        ll.push_back(l);
        rr.push_back(r);
    }

    std::sort(ll.begin(), ll.end());
    std::sort(rr.begin(), rr.end());


    for (int i=0; i<ll.size(); i++) {
        int diff = abs(rr[i] - ll[i]);
        std::cout << "current diff: " << diff << std::endl;

        output += diff;

    }
    std::cout << "output is: " << output;
    return output;
}


int main() {
    
    return sort_based();
}