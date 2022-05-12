#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <optional>

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
    unsigned int GetDistTo(const T& id);
    void PrintDists();
    void PrintGraf();

private:
    const int INF = 1e9;
    set <T> vertexes;
    map <T, vector <int>> graf;
    map <T, vector <int>> grafWeights;
    map <T, T> dists;
};

void debugPrintMap(map <int, int> m);

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
    std::map <T, T> dist, prev, used;
    for (auto v : vertexes) {
        dist[v] = INF;
    }
    // debugPrintMap(dist);
	dist[source] = 0;

	for (int i = 0; i < vertexes.size(); ++i) {
		optional <T> minVertex;
        // debugPrintMap(dist);
		for (auto vertex : vertexes) {
            if (!used[vertex] && (!minVertex || dist[vertex] < dist[*minVertex])) {
				minVertex = vertex;
            }
        }
			
		if (dist[*minVertex] == INF)
			break;

		used[*minVertex] = true;
        cout << "DEBUG: minVertex is: " << *minVertex << endl;
 
		for (int j = 0; j < graf[*minVertex].size(); ++j) {
			int to = graf[*minVertex][j];
			int	len = grafWeights[*minVertex][j];
			if (dist[*minVertex] + len < dist[to]) {
				dist[to] = dist[*minVertex] + len;
				prev[to] = *minVertex;
			}
		}
	}
    dists = dist;
}

template <class T>
unsigned int Dijkstra<T>::GetDistTo(const T& id) {
    return dists[id];
}


template <class T>
void Dijkstra<T>::PrintDists() {
    cout << "Print distances" << endl;
    for (auto v : dists) {
        cout << "dist to: " << v.first << " is: " << v.second << endl;
    }
    cout << endl;
}


void debugPrintMap(map <int, int> m) {
    cout << "Print map:" << endl;
    for (auto v : m) {
        cout << v.first << "   " << v.second << endl;
    }
    cout << endl;
}

template <class T>
void Dijkstra<T>::PrintGraf() {
    cout << "Print graf" << endl;
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