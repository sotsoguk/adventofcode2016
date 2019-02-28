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
bool checkABBA(const std::string& input)
{
    int len = input.size();
    int i = 0;
    while (i <= len-4) {
        if ( (input[i] != input[i+1]) && (input[i] == input[i+3]) && (input[i+1] == input[i+2]))
            return true;
        i++;
    }
    return false;
}
int main()
{
   
    std::ifstream ifs("input.txt", std::ifstream::in);
    auto input = std::vector<std::string>(read_input(ifs));
    std::regex pat {"\\w+"};
    std::smatch match;
    std::string tmp(input[0]);
    std::vector<std::vector<std::string>> codes;
    for (const auto& l: input)
    {
        std::vector<std::string> parts;
        std::string tmp(l);
         while (std::regex_search(tmp, match, pat))
        {
            //std::cout << match[0]<< std::endl;
            parts.push_back(match[0]);
            tmp = match.suffix();
        }
        codes.push_back(parts);
    }
    //Part 1
    int numTLS = 0;
    int numt = 0;
    for (const auto& l:codes)
    {
        // check even parts 
        bool isTLS = false;
        int i = 0;
        int numParts = l.size();
        while(i<numParts)
        {
             isTLS |= checkABBA(l[i]);
             i += 2;
        }   
        i = 1;
        if (!isTLS)
            continue;
        while (i < numParts)
        {
            if (checkABBA(l[i]))
                isTLS = false;
            i += 2;
        }
        if (isTLS)
            numTLS ++;
        // std::cout<<l[0]<<"["<<l[1]<<"]"<<l[2]<<" : ";
        // if ( ( checkABBA(l[0]) || checkABBA(l[2]) ) && !checkABBA(l[1]))
        //     {
        //         numTLS++;
        //         std::cout<<"TLS";
        //     }
        // std::cout<<std::endl;
        // numt++;
    }
    std::cout << "Part 1: " << numTLS << " of " << numt << std::endl;
    // std::cout << checkABBA("")

    // Part 2
    int cnt = 0;
    for (const auto& l: codes)
    {
        bool add = false;
        std::vector<std::string> aba; //outside []
        std::vector<std::string> bab;
        for (int i = 0; i <l.size();++i)
        {
            for (int j = 0; j <= l[i].size()-3;++j)
            {
                if (l[i][j] != l[i][j+1] && l[i][j] == l[i][j+2]){
                    // check if outside
                    if (i%2 == 0){
                        aba.emplace_back(l[i].substr(j,3));
                    }
                    else
                    {
                        std::string cand;
                        cand += l[i][j+1];
                        cand += l[i][j];
                        cand += l[i][j+1];
                        bab.emplace_back(cand);
                    }
                    
                }
            }
        }
        // check for candidates
        for (const auto& a:aba)
            for (const auto& b:bab)
            {
                if ( a == b)
                {
                    add = true;
                    break;
                }
            }
        if (add) cnt++;
    }
    std::cout << "Part 2:" << cnt << std::endl;
}
