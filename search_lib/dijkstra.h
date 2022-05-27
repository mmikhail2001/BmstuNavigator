#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <optional>
#include <algorithm>

using std::map;
using std::vector;
using std::set;
using std::cout;
using std::endl;
using std::optional;

template <class T>
class Dijkstra {
public:
    Dijkstra();
    void AddDirectedEdge(const T from, const T to, unsigned int weight);
    void FindRoute(const T source);
    optional <unsigned int> GetDistTo(const T& id);
    vector <T> GetRoadTo(const T& id);
    void PrintDist();
    void PrintGraf();

private:
    const int INF = 1e9;
    set <T> vertexes;
    map <T, vector <int> > graf;
    map <T, vector <int> > grafWeights;
    map <T, T> dist;
    map <T, T> prev;
    T sourceVertex;
};


template <class T>
Dijkstra<T>::Dijkstra() {}

template <class T>
void Dijkstra<T>::AddDirectedEdge(const T from, const T to, unsigned int weight) {
    vertexes.insert(from);
    vertexes.insert(to);
    graf[from].push_back(to);
    grafWeights[from].push_back(weight);
}


template <class T>
void Dijkstra<T>::FindRoute(const T source) {
    sourceVertex = source;
    prev.clear();
    dist.clear();
    std::map <T, T> used;
    for (auto v : vertexes) {
        dist[v] = INF;
    }
	dist[source] = 0;

	for (int i = 0; i < vertexes.size(); ++i) {
		optional <T> minVertex;
		for (auto vertex : vertexes) {
            if (!used[vertex] && (!minVertex || dist[vertex] < dist[*minVertex])) {
				minVertex = vertex;
            }
        }
			
		if (dist[*minVertex] == INF)
			break;
            

		used[*minVertex] = true;
 
		for (int j = 0; j < graf[*minVertex].size(); ++j) {
			int to = graf[*minVertex][j];
			int	len = grafWeights[*minVertex][j];
			if (dist[*minVertex] + len < dist[to]) {
				dist[to] = dist[*minVertex] + len;
				prev[to] = *minVertex;
			}
		}
	}
}

template <class T>
optional <unsigned int> Dijkstra<T>::GetDistTo(const T& id) {
    optional <unsigned int> optDist;
    if (dist[id] == INF) {
        return optDist;
    }
    optDist = dist[id];
    return optDist;
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

template <class T>
void Dijkstra<T>::PrintGraf() {
    for (auto v : graf) {
        cout << "vertex is: " << v.first << " array of edges: ";
        for (auto to : v.second) {
            cout << to << " ";
        }
        cout << endl;
        cout << " array of weights: ";
        for (auto weight : grafWeights[v.first]) {
            cout << weight << " ";
        }
        cout << endl;
    }
    cout << endl;
}