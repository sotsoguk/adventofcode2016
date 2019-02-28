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

bool checkTriangle(const int&a, const int&b, const int&c ){
    return  ( (a+b > c) && (a+c > b) && (b+c > a));
}
int main()
{
   
    std::ifstream ifs("input.txt", std::ifstream::in);
    auto input = std::vector<std::string>(read_input(ifs));
    //std::vector<std::string> toks = split(input[0],',');
    // std::cout<<input.size()
    //std::cout<<moveKeypad(1,'U')<<","<<moveKeypad(6,'D')<<","<<moveKeypad(7,'D')<<std::endl;
    // 
    std::vector<std::vector<int>> tris;
    std::regex pat {"\\d+"};
    for (const auto& line: input){
        std::string tmpLine(line);
        std::vector<int> tri;
        // std::cout << tmpLine;
        std::smatch match;
        while (std::regex_search(tmpLine, match, pat)){
            // std::cout<<match[0]<<",";
            tri.push_back(std::stoi(match[0]));
            tmpLine = match.suffix();

        }
        // std::cout <<"!!!    "<<tri[0]<<","<<tri[1]<<","<<tri[2];
        // std::cout<<std::endl;
        tris.push_back(tri);
        
    }
    // std::complex<int> c1(1,1);
    // std::cout<<pos2Char(c1);
    // Part 1
    int64_t numLegalTris = 0;
    for (const auto& t:tris)
    {
        // int sum = 0;
        int a = t[0];
        int b = t[1];
        int c = t[2];
        if ( (a+b > c) && (a+c > b) && (b+c > a))
            numLegalTris++;

    }   
    std::cout << "Part 1: " << numLegalTris << std::endl;
    // Part 2

    int numTris = tris.size();
    int numLegalTris2 = 0;
    int i = 0;
    while (i < numTris)
    {
        for (int j =0; j<3;j++){
            checkTriangle(tris[i][j], tris[i+1][j], tris[i+2][j]) && numLegalTris2++;
        }
        i += 3;

    }
    std::cout << "Part 2: " << numLegalTris2 << std::endl;
}
