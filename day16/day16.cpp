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

void genChecksum(std::string& input, size_t limit)
{
    input.reserve(limit*2); // double buffer size
    while (input.size() < limit)
    {
        input.push_back('0');
        auto b = input.rbegin();
        while (++b != input.rend())
        {
            input.push_back( *b ^1);
        }
    }
    input.resize(limit);
    while ( !(input.size() % 2))
    {
        auto i = input.begin();
        for (auto c = input.cbegin(); c!= input.cend(); c+=2)
        {
            *i++ = '0' + (*c == (*(c+1)));
        }
        input.resize(input.size() / 2);
    }

}

int main()
{
    std::string input("11110010111001001");
    const size_t LIMIT_1 = 272;
    const size_t LIMIT_2 = 35651584;
    std::cout << (17<<1) <<std::endl;
    genChecksum(input, LIMIT_2);
    std::cout << input<<std::endl;
}

