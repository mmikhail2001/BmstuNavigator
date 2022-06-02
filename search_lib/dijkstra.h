#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <optional>

using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::optional;
using std::set;
using std::pair;

template <class T>
class Dijkstra {
public:
    Dijkstra() {}

    void AddDirectedEdge(const T &from, const T& to, unsigned int weight);

    void FindRoute(const T& from);

    optional<unsigned int> GetDistTo(const T& to);

    vector <T> GetRoadTo(const T& id);

private:
    unordered_map <T, vector <pair <T, int>>> edges;
    unordered_map <T, optional <unsigned int>> dists;
    unordered_map <T, T> prev;
    T sourceVertex;

};

template <class T>
void Dijkstra<T>::AddDirectedEdge(const T &from, const T& to, unsigned int weight) {
    edges[from].push_back({to, weight});
}

template <class T>
void Dijkstra<T>::FindRoute(const T& from) {
    sourceVertex = from;
    set <pair<int, T>> tmpDists;
    tmpDists.insert({0, from});
    unordered_set <int> used;
    while (tmpDists.size()) {
        pair <int, T> minVertex = *(tmpDists.begin());
        used.insert(minVertex.second);
        tmpDists.erase(tmpDists.begin());
        for (auto &edge : edges[minVertex.second]) {
            T newVertex = edge.first;
            optional <unsigned int> lastDistToV = dists[newVertex];
            int nowDistToV = minVertex.first + edge.second;
            if (!used.count(newVertex) && (!lastDistToV || nowDistToV < lastDistToV)) {
                if (lastDistToV) {
                    pair <int, T> lastEdge = {*lastDistToV, newVertex};
                    tmpDists.erase(tmpDists.find(lastEdge));
                }
                dists[newVertex] = nowDistToV;
                tmpDists.insert({nowDistToV, newVertex});
                prev[newVertex] = minVertex.second;
            }
        }
    }
}

template <class T>
optional<unsigned int> Dijkstra<T>::GetDistTo(const T& to) {
    return dists[to];
}

template <class T>
vector <T> Dijkstra<T>::GetRoadTo(const T& id) {
    vector <T> path;
    for (T v = id; v != sourceVertex; v = prev[v]) {
        path.push_back(v);
    }
    path.push_back(sourceVertex);
    std::reverse(path.begin(), path.end());
    return path;
}

