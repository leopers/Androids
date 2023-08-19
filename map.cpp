#include "map.hpp"

Map::Map(std::vector<std::vector<bool>> & map)
        : grid{map}, gridHeight(map.size()), gridWidth(map[0].size())
{}

std::stack<pos> Map::dijsktra(pos src, pos end){
    std::priority_queue<pip, std::vector<pip>, std::greater<pip>> pq;
    std::set<pos> unvisitted;
    std::vector<std::vector<int>> dist;
    std::vector<std::vector<pos>> predecessor;

    dist.resize(gridWidth);
    predecessor.resize(gridWidth);
    for(int i=0; i<gridWidth; ++i){
        dist[i].resize(gridHeight, INT_MAX);
        predecessor[i].resize(gridHeight);
    } 

    for(int i=0; i<gridWidth; ++i)
        for(int j=0; j<gridHeight; ++j)
            unvisitted.insert({i,j});

    dist[src.fi][src.se] = 0;
    pq.push({0, src});

    std::vector<int> dx = {1, 0, -1, 0};
    std::vector<int> dy = {0, 1, 0, -1};

    while(!pq.empty()){
        auto u = pq.top().se;
        pq.pop();

        if(unvisitted.find(u) != unvisitted.end()){
            unvisitted.erase(u);

            for (int i=0; i<4; ++i){
                pos v = {u.fi + dx[i], u.se + dy[i]};
                if(v.fi>=gridWidth|| v.fi<0 || v.se>=gridHeight|| v.se<0 || grid[v.fi][v.se] == false)
                    continue;

                if(dist[v.fi][v.se] > dist[u.fi][u.se] + 1){
                    dist[v.fi][v.se] = dist[u.fi][u.se] + 1;
                    predecessor[v.fi][v.se] = {u.fi, u.se};
                    pq.push({dist[v.fi][v.se], v});
                }
            }
        }
    }

    std::stack<pos> path;
    while(end!=src){
        path.push(end);
        end = predecessor[end.fi][end.se];
    }

    return path;
}

std::stack<pos> Map::Astar(pos src, pos end){
    std::priority_queue<pip, std::vector<pip>, std::greater<pip>> pq;
    std::set<pos> unvisitted;
    std::vector<std::vector<double>> g;
    std::vector<std::vector<double>> f;
    std::vector<std::vector<pos>> predecessor;

    g.resize(gridWidth);
    f.resize(gridWidth);
    predecessor.resize(gridWidth);
    for(int i=0; i<gridWidth; ++i){
        g[i].resize(gridHeight, std::numeric_limits<double>::max());
        f[i].resize(gridHeight, std::numeric_limits<double>::max());
        predecessor[i].resize(gridHeight);
    } 

    for(int i=0; i<gridWidth; ++i)
        for(int j=0; j<gridHeight; ++j)
            unvisitted.insert({i,j});

    g[src.fi][src.se] = 0;
    f[src.fi][src.se] = heuristic(src, end);
    pq.push({f[src.fi][src.se], src});


    std::vector<double> dx = {1, 0, -1, 0};
    std::vector<double> dy = {0, 1, 0, -1};

    while(!pq.empty()){
        auto u = pq.top().se;
        pq.pop();

        if(u == end) break;

        if(unvisitted.find(u) != unvisitted.end()){
            unvisitted.erase(u);

            for (int i=0; i<4; ++i){
                pos v = {u.fi + dx[i], u.se + dy[i]};
                if(v.fi>=gridWidth|| v.fi<0 || v.se>=gridHeight|| v.se<0 || grid[v.fi][v.se] == false)
                    continue;

                if(f[v.fi][v.se] > g[u.fi][u.se] + heuristic(end, v)+1){
                    g[v.fi][v.se] = g[u.fi][u.se] + 1;
                    f[v.fi][v.se] = g[u.fi][u.se] + heuristic(end, v);
                    predecessor[v.fi][v.se] = {u.fi, u.se};
                    pq.push({f[v.fi][v.se], v});
                }
            }
        }
    }

    std::stack<pos> path;
    while(end!=src){
        path.push(end);
        end = predecessor[end.fi][end.se];
    }

    return path;
}

double heur(pos src, pos goal){
    return std::sqrt((src.fi-goal.fi)*(src.fi-goal.fi)+(src.se-goal.se)*(src.se-goal.se));
}
 