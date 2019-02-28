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

class Grid
{
public:
    Grid(size_t w, size_t h):  _grid(w,std::vector<int>(h,0)), width(w), height(h) {}
    int width, height;
    ~Grid() {_grid.clear();}
    void set(int x, int y);
    void setVal(int x, int y, int val);
    void clear(int x, int y);
    void rect(int x0, int y0, int x1, int y1);
     int  get(int x, int y);
    void rotateCol(int x, int steps);
    void rotateRow(int y, int steps);
    int64_t setPixels();
    void reset();
    friend std::ostream& operator<< (std::ostream &out,  Grid& g);
private:
    std::vector<std::vector<int>> _grid;

};

void Grid::rotateCol(int x, int steps){
    int rot = steps;
    if (rot == 0)
        return;
    else if (rot >0){
        rot %= height;
        rot = height - rot;
    }
    else {
        rot = - rot;
        rot %= height;
    }
        
    std::rotate(_grid[x].begin(), _grid[x].begin()+rot, _grid[x].end());
}

void Grid::rotateRow(int y, int steps){
    int rot = steps;
    if (rot == 0)
        return;
    else if (rot >0){
        rot %= width;
        rot = width - rot;
    }
    else {
        rot = - rot;
        rot %= width;
    }
    //copy row to temp vector
    std::vector<int> tmpRow;
    for (int x=0;x<width;++x)
        tmpRow.push_back(get(x,y));
    std::rotate(tmpRow.begin(),tmpRow.begin()+rot, tmpRow.end());

    //copy back
    for (int x=0;x<width;++x)
        setVal(x,y,tmpRow[x]);
}
void Grid::setVal(int x, int y, int val)
{
    _grid[x][y] = val;
}
void Grid::set(int x, int y)
{
    this->setVal(x, y, 1);
}

void Grid::clear(int x, int y)
{
    this->setVal(x,y,0);
}

int Grid::get(int x, int y)
{
    return this->_grid[x][y];
}
void Grid::rect(int x0, int y0, int x1, int y1)
{
    for (int x = x0; x<= x1;++x)
    {
        for (int y = y0; y<= y1;++y)
        {
            set(x,y);
        }
    }
}
int64_t Grid::setPixels()
{
    int64_t setPixs = 0;
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            if (get(x,y))
                setPixs++;
    return setPixs;
}

void Grid::reset()
{
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            setVal(x,y,0);
    
}

std::ostream& operator<< (std::ostream &out,  Grid& g)
{
    for (int j=0; j<g.height;++j)
    {
        for (int i=0;i<g.width;++i)
            {
                if (g.get(i,j))
                    out <<"#";
                else
                    out <<".";
            }
        out << std::endl;
    }
    return out;
}
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

void printDisplay(std::vector<std::vector<int>>& display)
{
    int width = display.size();
    int height = display[0].size();
    for (int j = 0;j < height; ++j)
    {
        for (int i=0; i< width; ++i)
        {
            if (display[i][j])
                std::cout<<"#";
            else
            {
                std::cout <<".";
            }
            
        }
        std::cout <<std::endl;
    }
}
int main()
{
   
    std::vector<std::vector<int>> display(50,std::vector<int>(6,0));
    display[0][1] = 1;
    display[49][5] = 1;
    std::ifstream ifs("input.txt", std::ifstream::in);
    auto input = std::vector<std::string>(read_input(ifs));
    std::vector<std::vector<std::string>> commands;
    std::vector<std::vector<int>> nums;
    for (const auto& l: input)
    {
        std::vector<std::string> toks = split(l,' ');
        std::vector<int> num(0);
        for (const auto& t:toks)
            std::cout << t<<",";
        commands.emplace_back(toks);
        // extract numbers
        std::regex pat {"\\d+"};    // find decimal numbers
        std::smatch match;
        std::string tmp(l);
        while ( std::regex_search(tmp, match, pat))
        {
            std::cout << match[0] <<",";
            num.push_back(std::stoi(match[0]));
            tmp = match.suffix();
        }
        nums.push_back(num);
        std::cout<<std::endl;
    }
    //printDisplay(display);
    Grid g(50,6);
    // g.set(49,5);
    // g.set(1,1);
    // g.set(2,2);
    // g.set(9,4);
    // g.rect(3,3,5,5);
    // std::cout << g;
    // g.rotateCol(3,-7);std::cout<<std::endl;
    // std::cout<< g;
    // std::cout<<std::endl;
    // g.rotateRow(5,2);
    // std::cout<<g;
    // std::cout << g.setPixels()<<std::endl;

    // parse inputs
    for (int i = 0; i< commands.size();++i)
    {
        // rect
        if (commands[i][0] == "rect")
        {
            g.rect(0,0,nums[i][0]-1,nums[i][1]-1);
            // std::cout << commands[i][0]<<":"<<nums[i][0]<<","<<nums[i][1]<<std::endl;
            // std::cout << g;
            // std::cout<<std::endl;
        }
        if (commands[i][0] == "rotate" && commands[i][1] == "column")
        {
            g.rotateCol(nums[i][0], nums[i][1]);
        }
        if (commands[i][0] == "rotate" && commands[i][1] == "row")
        {
            g.rotateRow(nums[i][0], nums[i][1]);
        }
        // std::cout << commands[i][0]<<":"<<nums[i][0]<<","<<nums[i][1]<<std::endl;
        // std::cout << g;
        // std::cout<<std::endl;
    }
    std::cout << g <<std::endl;
    std::cout <<"Part 1: " << g.setPixels() << std::endl;
}

