#pragma once
#include <vector>
#include <iterator>
#include <algorithm>
#include "points.h"
#include "database.h"
#include "dijkstra.h"

using std::vector;

class Route {
    std::vector <Edge> edges;
public:
    void AddEdge(Edge edge) {
        edges.push_back(edge);
    }
    std::vector <Edge> GetEdges() { return edges; }
    unsigned int Size() { return edges.size(); }
    void Reverse() { std::reverse(edges.begin(), edges.end()); }
};

class Search {

    std::vector <BasePoint> graf;
    std::vector <Infrastructure> infr;
    std::map <std::string, std::vector <Point*> > namePointsMap;
    std::map <unsigned int, Point*> idPointMap;
    Dijkstra <unsigned int> dijkstraSearcher;

    // std::map <unsigned int, Infrastructure*> idInfrMap;
    // std::map <unsigned int, BasePoint*> idBasePointsMap;


    void createMapPoints(std::vector <Point*> points);
    void initMaps();
    void initDijkstra();


public:
    // enum class Exeptions { UNKNOWN_POINT };
    Search(DataBase* base);
    bool HavePoint(std::string name);
    Point* GetById(unsigned int id);
    vector <Point*> GetByName(std::string name);
    Route FindRoute(unsigned int id, std::string name);
    bool IsUniquePoint(std::string name);
};