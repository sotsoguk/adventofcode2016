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

struct Eq
{
    int rem;
    int mod;
    Eq(): rem(0), mod(0) {};
    Eq(int r, int m): rem(r), mod(m) {};
};

int modInverse(int num, int mod)
{
    int cand = 1;
    num %= mod;
    while (cand < mod)
    {
        if ( (num*cand) % mod == 1)
        {
            return cand;
        }
        cand++;
    }
    return 0;
}

int64_t mod(int64_t x, int64_t y)
{
    return (x<0) ? (x%y + y): (x%y);
}

int64_t gcd(int64_t a, int64_t b)
{
    if (a < b)
        std::swap(a,b);
    while (b>0)
    {
        int64_t t = a%b;
        a = b;
        b = t;
    }
    return a;
}

int64_t solveCRT(const std::vector<Eq>& eqs)
{
    size_t n = eqs.size();
    int64_t m = 1;
    std::vector<int64_t> z(n,0);
    std::vector<int64_t> w(n,0);
    std::vector<int64_t> y(n,0);
    for (const auto& e:eqs)
        m *= e.mod;
    for (size_t i=0; i<n; ++i)
    {
        z[i] = m / eqs[i].mod;
        y[i] = modInverse(z[i],eqs[i].mod);
        w[i] = (y[i] * z[i]) % m;

    }
    int64_t solution = 0;
    for (int i=0;i<n;++i)
        solution += (eqs[i].rem * w[i]);
    return mod(solution,m);
}
int main()
{
    std::cout << mod(-20,7) << std::endl;
    std::cout << gcd(20,8)<<"," << gcd(117, 39)<<"," << gcd(111, 99)<<std::endl;
    std::cout<<"17 ^-1 (13) = " << modInverse(17,13)<<std::endl;
    std::cout<<"13 ^-1 (17) = " << modInverse(13,17)<<std::endl;
    std::vector<Eq> eqs;
    eqs.push_back(Eq(2,13));
    eqs.push_back(Eq(0,17));
    eqs.push_back(Eq(18,19));
    eqs.push_back(Eq(2,7));
    eqs.push_back(Eq(0,5));
    eqs.push_back(Eq(2,3));
    eqs.push_back(Eq(4,11));
    std::cout<<solveCRT(eqs)<<std::endl;

   
}

