#pragma once
#include <vector>
#include <iterator>
#include <algorithm>
#include <optional>
#include "points.h"
#include "database.h"
#include "dijkstra.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::optional;

class Route {
    std::vector <Edge> edges;
    std::vector <string> links;
public:
    void AddEdge(Edge edge) { edges.push_back(edge); links.push_back(edge.linkToFile); }
    std::vector<Edge> GetEdges() { return edges; }
    unsigned int Size() { return edges.size(); }
    void Reverse() { std::reverse(edges.begin(), edges.end()); }
    vector<string>::iterator begin() { return links.begin(); }
    vector<string>::iterator end() { return links.end(); }
    vector<string> GetLinks() { return links; }
};

class Search {

    std::vector <BasePoint> graf;
    std::vector <Infrastructure> infr;
    std::map <std::string, std::vector <Point*> > namePointsMap;
    std::map <unsigned int, Point*> idPointMap;
    Dijkstra <unsigned int> dijkstraSearcher;

    void createMapPoints(std::vector <Point*> points);
    void initMaps();
    void initDijkstra();

public:
    Search(DataBase* base);
    bool HavePoint(std::string name);
    Point* GetById(unsigned int id);
    vector <Point*> GetByName(std::string name);
    optional <Route> FindRoute(unsigned int id, std::string name);
    bool IsUniquePoint(std::string name);
};