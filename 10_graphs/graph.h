//
// Created by musht on 05.03.2023.
//

#ifndef ALGORITHMS2_GRAPH_H
#define ALGORITHMS2_GRAPH_H

#include <vector>
#include <iostream>

using vertex = int;
using edge = std::pair<vertex, vertex>;
using vertices = std::vector<vertex>;
struct weighted_edge {
    vertex from, to;
    double weight;
};
using weighted_vertex = std::pair<vertex, double>;

struct Graph {
    std::vector<vertices> adj;
    explicit Graph(int n) : adj(n) {}
    Graph(int size, std::initializer_list<edge> li) : Graph(size) {
        for (auto & e : li) {
            add_edge(e.first, e.second);
        }
    }

    void add_edge(vertex u, vertex v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int size() const {
        return (int) adj.size();
    }

    void print() const {
        for (int i = 0; i < adj.size(); ++i) {
            std::cout << i << ": [";
            for (auto v : adj[i]) {
                std::cout << v << ", ";
            }
            std::cout << "]\n";
        }
    }
};

struct Orgraph {
    std::vector<vertices> out;
    std::vector<vertices> in;

    explicit Orgraph(int n) : out(n), in(n) {}
    Orgraph(int size, std::initializer_list<edge> li) : Orgraph(size) {
        for (auto & edge : li) {
            add_edge(edge.first, edge.second);
        }
    }

    void add_edge(int u, int v) {
        out[u].push_back(v);
        in[v].push_back(u);
    }

    void print() const {
        for (int i = 0; i < out.size(); ++i) {
            std::cout << i << ": in[";
            for (auto v : in[i]) {
                std::cout << v << ", ";
            }
            std::cout << "], out[";
            for (auto v : out[i]) {
                std::cout << v << ", ";
            }
            std::cout << "]\n";
        }
    }
};

struct WeightedGraph {
    std::vector<std::vector<weighted_vertex>> adj;
    explicit WeightedGraph(int n) : adj(n) {}
    WeightedGraph(int size, std::initializer_list<weighted_edge> li) : WeightedGraph(size) {
        for (auto & e : li) {
            add_edge(e);
        }
    }

    void add_edge(weighted_edge we) {
        adj[we.from].emplace_back(we.to, we.weight);
        adj[we.to].emplace_back(we.from, we.weight);
    }

    int size() const {
        return (int) adj.size();
    }

    void print() const {
        for (int i = 0; i < adj.size(); ++i) {
            std::cout << i << ": [";
            for (auto [v, w] : adj[i]) {
                std::cout << v << "("<< w <<"), ";
            }
            std::cout << "]\n";
        }
    }
};


#endif //ALGORITHMS2_GRAPH_H
