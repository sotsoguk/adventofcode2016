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
    auto hash = [] (const std::complex<int>& p) { return p.real()*31 + p.imag();};
    std::unordered_set<std::complex<int>, decltype(hash)> prevPos(8,hash);
    std::ifstream ifs("input.txt", std::ifstream::in);
    auto input = std::vector<std::string>(read_input(ifs));
    std::vector<std::string> toks = split(input[0],',');
    std::vector<std::pair<std::complex<int>,int>> instructions;
    for (const auto& x: toks){
        
        //std::cout<<x<<"!!"<<"\t";
        std::regex pat {"\\d+"};
        std::smatch match;
        if ( std::regex_search(x, match, pat)){
            if (x.at(1) == 'L')
                 instructions.emplace_back(std::make_pair(std::complex<int>(0,1),std::stoi(match[0])));
            else
            {
                 instructions.emplace_back(std::make_pair(std::complex<int>(0,-1),std::stoi(match[0])));
            }
            
            //std::cout << "!"<<x.at(1)<<"+"<<match[0]<<"!"<<std::endl;
        }

    }

    // for (const auto& x:instructions)
    //     std::cout <<x.first<<","<<x.second<<std::endl;
    std::complex<int> pos(0,0);
    std::complex<int> dir(0,1);
    prevPos.insert(pos);
    std::set<int> dists;
    for (const auto& x: instructions){
        dir *= x.first;
        auto steps = x.second;
        for (auto i=0;i<steps;++i){
            pos += dir;
            if (prevPos.count(pos)){
                std::cout<<"Found:"<<pos<<"\n";
                dists.insert(std::abs(pos.real()) + std::abs(pos.imag()));
            }
            prevPos.insert(pos);
        }
        // pos += (x.second * dir);
        // if (prevPos.count(pos))
        //     std::cout<<"Found:"<<pos<<"\n";
        
        // prevPos.insert(pos);
        
        
    }
    std::cout<<"Final Position: " << pos<<std::endl;
    std::cout<<"Part 1: "<< std::abs(pos.real())+std::abs(pos.imag())<< std::endl;
    std::cout<<"Part 2: "<< *dists.begin()<<std::endl;
}
