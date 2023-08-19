#ifndef MAP_CPP
#define MAP_CPP

#include <climits>
#include <functional>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <cmath>
#include <limits>
#include <stack>

using pos = std::pair<int, int>;
using pip = std::pair<int, pos>;
#define fi first
#define se second

class Map{
public:
    Map(std::vector<std::vector<bool>> & map);
    std::stack<pos> dijsktra(pos src, pos goal);
    std::stack<pos> Astar(pos src, pos goal);

private:
    std::vector<std::vector<bool>> grid;
    int gridWidth, gridHeight;
};

double heuristic(pos src, pos goal);

#endif