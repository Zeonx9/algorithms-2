//
// Created by musht on 05.03.2023.
//

#ifndef ALGORITHMS2_GRAPH_ALGS_H
#define ALGORITHMS2_GRAPH_ALGS_H

#include <queue>
#include "graph.h"

void dfs_private(
        std::vector<int> &time_in,
        std::vector<int> &time_out,
        std::vector<int> &color,
        int &timer,
        const Graph &g,
        int v
        ) {
    time_in[v] = timer++;
    color[v] = 1;
    for (auto u : g.adj[v]) {
        if (color[u] != 0)
            continue;
        dfs_private(time_in, time_out, color, timer, g, u);
    }
    color[v] = 2;
    time_out[v] = timer++;
}

std::pair<std::vector<int>, std::vector<int>> dfs(const Graph &g, int v) {
    std::vector<int> time_in(g.size(), 0), time_out(g.size(), 0), color(g.size(), 0);
    int timer = 0;
    dfs_private(time_in, time_out, color, timer, g, v);
    return {time_in, time_out};
}

void private_bridges(
        std::vector<int> &time_in,
        std::vector<int> &time_up,
        std::vector<bool> &used,
        std::vector<edge> &bridges,
        int &timer,
        const Graph &g,
        int v,
        int p
        ) {
    time_up[v] = time_in[v] = timer++;
    used[v] = true;
    for (auto u: g.adj[v]) {
        if (u == p) {
            continue;
        }
        if (used[u]) {
            time_up[v] = std::min(time_up[v], time_in[u]);
        }
        else {
            private_bridges(time_in, time_up, used, bridges, timer, g, u, v);
            time_up[v] = std::min(time_up[v], time_up[u]);
            if (time_up[u] > time_up[v]) {
                bridges.emplace_back(v, u);
            }
        }
    }
}

std::vector<edge> find_bridges(const Graph &g) {
    std::vector<int> time_int(g.size(), 0), time_up(g.size(), 0);
    std::vector<bool> used(g.size(), false);
    std::vector<edge> bridges;
    int timer = 0;
    private_bridges(time_int, time_up, used, bridges, timer, g, 0, -1);
    return bridges;
}


std::vector<int> bfs(const Graph &g, vertex s) {
    std::vector<int> dist(g.size(), -1);
    std::queue<vertex> queue;
    dist[s] = 0;
    queue.push(s);
    while (!queue.empty()) {
        auto u = queue.front();
        queue.pop();
        for (auto v : g.adj[u]) {
            if (dist[v] != -1) {
                continue;
            }
            dist[v] = dist[u] + 1;
            queue.push(v);
        }
    }
    return dist;
}

std::vector<double> dijkstra(const WeightedGraph &g, vertex s) {
    const int  INF = 100000000;
    std::vector<double> dist(g.size(), INF);
    auto comp = [](const weighted_vertex &e1, const weighted_vertex &e2) {
        return e1.second >= e2.second;
    };
    std::priority_queue<weighted_vertex, std::vector<weighted_vertex>, decltype(comp)> queue(comp);
    dist[s] = 0;
    queue.emplace(s, 0);

    while (!queue.empty()) {
        auto [v, l] = queue.top();
        queue.pop();

        if (l != dist[v])
            continue;

        for (auto [u, w] : g.adj[v]) {
            if (l + w < dist[u]) {
                dist[u] = l + w;
                queue.emplace(u, l + w);
            }
        }
    }
    for (auto &d : dist) {
        if (d == INF)
            d = -1;
    }
    return dist;
}

#endif //ALGORITHMS2_GRAPH_ALGS_H
