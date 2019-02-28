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
char pos2Char(const std::complex<int>& pos){

    auto hash = [] (const std::complex<int>& p) { return p.real()*31 + p.imag();};
    std::unordered_map<std::complex<int>,char, decltype(hash)> keyPad(8,hash);

    // fill keyPad
    keyPad[{0,0}] = '7';
    keyPad[{1,0}] = '8';
    keyPad[{2,0}] = '9';
    keyPad[{-1,0}] = '6';
    keyPad[{-2,0}] = '5';
    keyPad[{1,1}] = '4';
    keyPad[{0,1}] = '3';
    keyPad[{-1,1}] = '2';
    keyPad[{0,2}] = '1';
    keyPad[{-1,-1}] = 'A';
    keyPad[{0,-1}] = 'B';
    keyPad[{1,-1}] = 'C';
    keyPad[{0,-2}] = 'D';
    return keyPad[pos];
}
std::complex<int> moveHexPad(const std::complex<int>& currPos, const char& dir)
{
    std::complex<int> tmpPos(currPos);
    std::complex<int> up(0,1);
    std::complex<int> right(1,0);
    if (std::toupper(dir) == 'R'){
        tmpPos+= right;
    }
    if (std::toupper(dir) == 'L'){
        tmpPos -= right;
    }
    if (std::toupper(dir) == 'U'){
        tmpPos += up;
    }
    if (std::toupper(dir) == 'D'){
        tmpPos -= up;
    }
    if (std::abs(tmpPos.real()) + std::abs(tmpPos.imag()) <= 2)
        return tmpPos;
    else
    {
        return currPos;
    }
    
}

int moveKeypad(int currPos, const char& dir){
    if (std::toupper(dir) == 'R'){
        return (currPos % 3) ? ++currPos : currPos; 
    }
    if (std::toupper(dir) == 'L'){
        return (currPos % 3 == 1) ? currPos: --currPos;
    }
    if (std::toupper(dir) == 'U'){
        return (currPos < 4) ? currPos: currPos-3;
    }
    if (std::toupper(dir) == 'D'){
        return (currPos > 6) ? currPos: currPos+3;
    }
    return 0;
}
int main()
{
   
    std::ifstream ifs("input.txt", std::ifstream::in);
    auto input = std::vector<std::string>(read_input(ifs));
    //std::vector<std::string> toks = split(input[0],',');
    // std::cout<<input.size()
    //std::cout<<moveKeypad(1,'U')<<","<<moveKeypad(6,'D')<<","<<moveKeypad(7,'D')<<std::endl;
    // 
    
    // std::complex<int> c1(1,1);
    // std::cout<<pos2Char(c1);
    
    std::complex<int> pos(-2,0);
    for (const auto& line: input)
    {
        for (const char& c: line)
        {
            pos = moveHexPad(pos,c);
           // std::cout<<pos<<"\t";
        }
        std::cout<<pos2Char(pos)<<",";
    }
    // std::cout<<pos<<std::endl;
}
