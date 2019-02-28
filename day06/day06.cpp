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


int main()
{
   
    std::ifstream ifs("input.txt", std::ifstream::in);
    auto input = std::vector<std::string>(read_input(ifs));
    int lenCode = input[0].size();
    std::cout << "CodeLength: " << lenCode << std::endl;
    std::vector<std::map<char,int>> codes(lenCode);
    //Part 1
    for (const auto& line: input)
    {
        for (std::size_t i = 0; i < lenCode; ++i)
        {
            codes[i][line[i]]++;
        }
    }
    // for (const auto& i:codes[1])
    //     std::cout<< i.first<<"," <<i.second<<"\n";
    // auto x = std::max_element(codes[1].begin(), codes[1].end(),
    // [](const pair<int, int>& p1, const pair<int, int>& p2) {
    //     return p1.second < p2.second; });
    auto x = std::max_element(codes[1].begin(), codes[1].end(),
    [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return p1.second < p2.second; });
    std::cout << x->first<<"!!" << x->second;
    std::cout << std::endl;
    for (std::size_t i=0; i < lenCode; ++i)
    {
        auto x = std::min_element(codes[i].begin(), codes[i].end(),
    [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return p1.second < p2.second; });
        std::cout<<x->first<<",";
    }
}
