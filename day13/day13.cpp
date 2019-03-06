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

struct Pos
{
    int x;
    int y;
    int val;
    Pos(): x(0), y(0), val(0) {};
    Pos(int a, int b, int v): x(a), y(b), val(v) {};
};

class Grid
{
  public:
    Grid(size_t w, size_t h) : _grid(w, std::vector<int>(h, 0)), _flag(w, std::vector<bool>(h, false)), width(w), height(h) {}
    int width, height;
    ~Grid() { _grid.clear(); }
    void set(int x, int y);
    void setVal(int x, int y, int val);
    void clear(int x, int y);
    void rect(int x0, int y0, int x1, int y1);
    int get(int x, int y);
    void rotateCol(int x, int steps);
    void rotateRow(int y, int steps);
    void setFlag(int x, int y, bool status = true);
    bool getFlag(int x, int y);
    int64_t setPixels();
    void reset();
    friend std::ostream &operator<<(std::ostream &out, Grid &g);

  private:
    std::vector<std::vector<int>> _grid;
    std::vector<std::vector<bool>> _flag;
};

bool Grid::getFlag(int x, int y)
{
    return _flag[x][y];
}
void Grid::setFlag(int x, int y, bool status)
{
    _flag[x][y] = status;
}
void Grid::rotateCol(int x, int steps)
{
    int rot = steps;
    if (rot == 0)
        return;
    else if (rot > 0)
    {
        rot %= height;
        rot = height - rot;
    }
    else
    {
        rot = -rot;
        rot %= height;
    }

    std::rotate(_grid[x].begin(), _grid[x].begin() + rot, _grid[x].end());
}

void Grid::rotateRow(int y, int steps)
{
    int rot = steps;
    if (rot == 0)
        return;
    else if (rot > 0)
    {
        rot %= width;
        rot = width - rot;
    }
    else
    {
        rot = -rot;
        rot %= width;
    }
    //copy row to temp vector
    std::vector<int> tmpRow;
    for (int x = 0; x < width; ++x)
        tmpRow.push_back(get(x, y));
    std::rotate(tmpRow.begin(), tmpRow.begin() + rot, tmpRow.end());

    //copy back
    for (int x = 0; x < width; ++x)
        setVal(x, y, tmpRow[x]);
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
    this->setVal(x, y, 0);
}

int Grid::get(int x, int y)
{
    if (x<0 || x>=width || y < 0 || y>= height)
        return -1;
    return this->_grid[x][y];
}
void Grid::rect(int x0, int y0, int x1, int y1)
{
    for (int x = x0; x <= x1; ++x)
    {
        for (int y = y0; y <= y1; ++y)
        {
            set(x, y);
        }
    }
}
int64_t Grid::setPixels()
{
    int64_t setPixs = 0;
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            if (get(x, y))
                setPixs++;
    return setPixs;
}

void Grid::reset()
{
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            setVal(x, y, 0);
}

std::ostream &operator<<(std::ostream &out, Grid &g)
{
    for (int j = 0; j < g.height; ++j)
    {
        for (int i = 0; i < g.width; ++i)
        {
            if (g.get(i, j) == INT_MAX)
                out << "#";
            else if (g.get(i, j) == 0)
                out << ".";
            //else if (g.get(i, j) == 3)
              //  out << "O";
            else
                out << g.get(i,j);
        }
        out << std::endl;
    }
    return out;
}
std::vector<std::string> split(const std::string &str, const char &delim = ',')
{
    std::stringstream ss(str);
    std::string token;
    std::vector<std::string> toks;
    while (std::getline(ss, token, delim))
    {
        toks.push_back(token);
    }
    return toks;
}

void printDisplay(std::vector<std::vector<int>> &display)
{
    int width = display.size();
    int height = display[0].size();
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            if (display[i][j])
                std::cout << "#";
            else
            {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}
void constructMaze(Grid &g, int favNum)
{
    for (int x = 0; x < g.width; ++x)
    {
        for (int y = 0; y < g.height; y++)
        {
            int64_t tmp = x + y;
            int64_t n = tmp * tmp + tmp + 2 * x + favNum;
            int oneCount = n & 1 ? 1 : 0;
            while (n = n >> 1)
            {
                if (n & 1)
                    ++oneCount;
            }

            if (oneCount % 2)
                g.setVal(x, y, INT_MAX);
        }
    }
}
void computePath(Grid& g)
{
    Pos p(1,1,0);
    //g.setFlag(p.x,p.y, true);
    std::deque<Pos> deq;
    deq.push_front(p);
    while (! deq.empty())
    {
        Pos curr = deq.front();
        deq.pop_front();
        g.setVal(curr.x,curr.y,curr.val);
        //g.setFlag(curr.x, curr.y);

        if (g.get(curr.x+1, curr.y) == 0 || ( g.get(curr.x+1, curr.y) > curr.val+1 && g.get(curr.x+1, curr.y) < INT_MAX ))//<= curr.val 0 && !g.getFlag(curr.x+1, curr.y))
            deq.emplace_front(Pos(curr.x+1,curr.y,curr.val+1));
        
        if (g.get(curr.x, curr.y+1) == 0 || ( g.get(curr.x, curr.y+1) > curr.val +1 && g.get(curr.x, curr.y+1) < INT_MAX   ) )//&& !g.getFlag(curr.x, curr.y+1))
            deq.emplace_front(Pos(curr.x,curr.y+1,curr.val+1));
        if (g.get(curr.x-1, curr.y) == 0  || ( g.get(curr.x-1, curr.y) > curr.val+1 && g.get(curr.x-1, curr.y) < INT_MAX ))//&& !g.getFlag(curr.x-1, curr.y))
            deq.emplace_front(Pos(curr.x-1,curr.y,curr.val+1));
        
        if (g.get(curr.x, curr.y-1) == 0 || ( g.get(curr.x, curr.y-1)> curr.val +1  && g.get(curr.x, curr.y-1) < INT_MAX )) //&& !g.getFlag(curr.x, curr.y-1))
            deq.emplace_front(Pos(curr.x,curr.y-1,curr.val+1));
        

    }
}
int main()
{

    Grid g(50, 50);
    constructMaze(g, 1352);
    //g.setVal(31, 39, 2);
    std::cout << g;
    // std::cout << g.get(-1,10);
    std::cout <<std::endl;
    computePath(g);
    std::cout << g;
    std::cout <<g.get(31,39);
    int reachable = 0;
    for (int x = 0; x<g.width;++x)
        for (int y = 0; y<g.height; ++y)
            if (g.get(x,y) >0 && g.get(x,y)<= 50)
                reachable++;
    std::cout << reachable;
}
