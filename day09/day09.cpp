#include "../reader.hpp"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <utility>
#include <complex>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <numeric>
#include <map>


std::vector<std::string> split(const std::string& str, const char& delim=',')
{
    std::stringstream ss(str);
	std::string token;
	std::vector<std::string> toks;
	while(std::getline(ss, token, delim)) {
		toks.push_back(token);
	}
    return toks;
}
int lengthDecode(const std::string& str)
{
    std::string input(str);
    std::string output;
    int len = input.size();
    int i = 0;
    while (i < len)
    {   
        // normal character => copy
        if (input[i] != '(')
        {
            if (input[i] != ' ')
                output += input[i];
            ++i;
        }
        // start of 
        else{
            int j = i+1;
            std::string firstNum;
            std::string secondNum;
            while (input[j] != 'x')
            {
                firstNum += input[j];
                j++;
            }
            int charsRepeat = std::stoi(firstNum);
            j++;
            while (input[j] != ')')
            {
                secondNum += input[j];
                j++;
            }
            int numRepeat = std::stoi(secondNum);
            //std::cout <<charsRepeat<<"x"<<numRepeat<<std::endl;
            j++;
            int tmpIndex = 0;
            std::string dupl;
            while (tmpIndex < charsRepeat)
            {
                dupl+= input[j+tmpIndex];
                tmpIndex++;
            }
            for (int i=0;i<numRepeat;++i)
                output+=dupl;
            j += charsRepeat;
            i = j;
        }
        
    }
    // std::cout << std::endl<< "Decoded: " << output<<std::endl;
    return output.size();

}
int main()
{
    int64_t numChars = 0;
    // std::cout << lengthDecode("X(8x2)(3x3)ABCY");
    std::ifstream ifs("input.txt", std::ifstream::in);
    auto input = std::vector<std::string>(read_input(ifs));
    for (const auto& l:input)
    {
        numChars += lengthDecode(l);

    }
    std::cout <<"Part 1: " <<numChars;
}

