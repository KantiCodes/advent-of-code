#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include <iostream>
#include <fstream>
#include <string>


int getMuls(std::string input){
    int output=0;
    std::regex word_regex(R"(mul\((\d+),(\d+)\))");
    auto begin = std::sregex_iterator(input.begin(), input.end(), word_regex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        std::smatch match = *it;
        int num1 = std::stoi(match[1].str()); // First number
        int num2 = std::stoi(match[2].str()); // Second number
        output += num1 * num2;
    }
    return output;
    
}

int inplace() {
    std::string input;
    
    // std::cin >> input;
    
    std::ifstream myfile; myfile.open("2024/day3/one.in");

    if (!myfile.good() || !myfile.is_open()){
        std::cout << "File does not exist";
        return 1;
    }

    bool anyDonts = false;

    std::regex dont_regex(R"((don't\(\)[\s\S]*?(?=(do\(\))|$)))");

    std::stringstream result;


    input.assign((std::istreambuf_iterator<char>(myfile)),
              std::istreambuf_iterator<char>());


    std::regex_replace(std::ostream_iterator<char>(result), input.begin(), input.end(), dont_regex, "");

    std::cout<<input << std::endl;
    std::cout<< result.str() << std::endl;

    
    std::cout<<"Part one result: " << getMuls(input) << std::endl;
    std::cout<<"Part two result: " << getMuls(result.str()) << std::endl;

    return 0;

}


int main() {
    int output = inplace();
    return 0;
}