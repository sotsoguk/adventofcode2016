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
#include <deque>
#include <bitset>
#include <list>

#define INPUT 3012210
int64_t josephus( int64_t n)
{
    int64_t m = floor( log(n) / log(2));
    int64_t l = n - pow(2,m);
    int64_t j = 2*l +1;

    return j;
}
int64_t getNext(std::bitset<INPUT>& circle, int64_t pos)
{
    int64_t p = pos;
    while (! circle[p])
    {   
        //std::cout <<"!"<<p<<"\t";
        p = (p+1) % INPUT;
    }
    return p;
}

int64_t getAhead(std::bitset<INPUT>& circle, int64_t pos, int64_t steps)
{
    while (steps)
    {
        pos = (pos +1) % INPUT;
        if (circle[pos])
            steps--;
    }
    return pos;
}
void solvePart2(std::list<int64_t>& l)
{
    auto toKill = l.begin();
    std::advance(toKill, floor(INPUT / 2));
    auto act = l.begin();
    while (l.size() > 1)
    {
        toKill = l.erase(toKill);
        if (toKill == l.end())
            toKill = l.begin();
        if (l.size() % 2 == 0)
        {
            toKill++;
            if (toKill == l.end())
                toKill = l.begin();
        }
        act++;
        if (act == l.end())
            act = l.begin();
    }
    std::cout << *l.begin()<<std::endl;

}
int main()
{
    const int64_t input = 3012210;
    std::cout <<"Part 1: " << josephus(input) << std::endl;
    // std::bitset<INPUT> circle;
    // for (int i=0;i<INPUT;++i)
    //     circle[i] = true;
    // int64_t numActive = INPUT;
    // int64_t pos = 0;
    // int64_t round = 1;
    // while (numActive>1)
    // {
    //     // std::cout << "Round:" <<round <<":"<<numActive<<std::endl;
    //     int64_t d = floor(numActive / 2);
    //     int64_t toCancel = getAhead(circle, pos,d );
    //     //std::cout << "toCancel : " << toCancel <<"\n";
    //     circle[toCancel] = false;
    //     numActive--;
    //     pos = getNext(circle,pos +1);
    //     round ++;
    //     // std::cout <<"Active: ";
    //     // for (int i=0;i<INPUT;++i)
    //     //     if (circle[i])
    //     //         std::cout<<i<<",";
    //     // std::cout << "\n";
    //     if (numActive % 1000)
    //         std::cout << numActive <<"\n";
    // }
    // std::cout << getNext(circle, 0);

    // Part2
    std::list<int64_t> p2;
    for (int i=0; i<input;++i)
        p2.emplace_back(i+1);
    solvePart2(p2);
}
