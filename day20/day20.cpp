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
#include <chrono>

using namespace std::chrono;

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
struct Range
{
  int64_t min;
  int64_t max;
  Range(int64_t a, int64_t b): min(a), max(b){};
  Range():min(0),max(UINT_FAST32_MAX){}; 
  int64_t numElems() const {return max - min +1;};
};

bool operator<(const Range &r1, const Range &r2)
{
    return r1.min < r2.min;
}
int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
    int64_t numChars = 0;
    std::ifstream ifs("input.txt", std::ifstream::in);
    auto input = std::vector<std::string>(read_input(ifs));
    std::vector<Range> toBlock;
    for (const auto& l:input)
    {
        std::vector<std::string> tmp = split(l,'-');
        toBlock.emplace_back(Range(std::stol(tmp[0]), std::stol(tmp[1])));
    }
    std::sort(toBlock.begin(), toBlock.end());
    
    std::vector<Range> merged;
    int64_t min = 0;
    int64_t max = 0;
    for (const auto& i: toBlock){
        auto tmin = i.min;
        auto tmax = i.max;
        if (tmin <= max+1){
            max = std::max(tmax, max);
        }
        else{
            merged.emplace_back(Range(min,max));
            min = tmin;
            max = tmax;
        }
    }
    merged.emplace_back(Range(min, max));
    int64_t numBlocked = 0;
    for (const auto& i:merged)
    {
        numBlocked += i.numElems();
        
    }   
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    std::cout << "Part 1: " <<merged[0].max +1 <<std::endl;
    std::cout << "Part 2: " << 4294967296 - numBlocked << std::endl;
    std::cout << duration << std::endl;
    
}

