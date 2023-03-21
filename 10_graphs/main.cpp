
#include "graph_algs.h"

int main() {
    Graph g(5, {{0, 2}, {1, 2}, {4, 0}, {3, 1}, {2, 4}});
    g.print();
    auto [in, out] = dfs(g, 0);
    std::cout << "dfs\n";
    for (int i = 0; i < g.size(); ++i) {
        std::cout << i << ": " << "in = " << in[i] << ", out=" << out[i] << ";\n";
    }
    std::cout << "bridges\n";
    auto bridges = find_bridges(g);
    for (auto [v, u] : bridges) {
        std::cout << "(" << v << ", " << u << ");\n";
    }
    std::cout << "bfs (0 -> )\n";
    auto dist = bfs(g, 0);
    for (int i = 0; i < g.size(); ++i) {
        std::cout << i << ": " << dist[i] << ";\n";
    }
    std::cout << "dijkstra (0 -> )\n";
    WeightedGraph gw(5, {{0, 2, 1}, {1, 2, 4}, {4, 0, 3}, {3, 1, 6}, {2, 4, 7}});
    gw.print();
    auto dist_w = dijkstra(gw, 0);
    for (int i = 0; i < g.size(); ++i) {
        std::cout << i << ": " << dist_w[i] << ";\n";
    }
}