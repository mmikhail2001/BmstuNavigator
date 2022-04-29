#pragma once
#include <vector>
#include <iterator>
#include <algorithm>
#include "points.h"
#include "database.h"




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
    struct DistToPointWithPoint {
        unsigned int dist;
        Point* point;
        DistToPointWithPoint() : dist(0), point(nullptr) {}
        DistToPointWithPoint(int dist, Point* point) : dist(dist), point(point) {}
    };
    struct DistToPointWithEdge {
        unsigned int dist;
        Edge edge;
        DistToPointWithEdge() : dist(0), edge(0, 0, 0, "") {}
        DistToPointWithEdge(int dist, Edge edge) : dist(dist), edge(edge) {}
    };

    class IsGreater {
    public:
        bool operator ()(const DistToPointWithPoint &l, const DistToPointWithPoint &r) {
            return l.dist > r.dist;
        }
    };

    std::vector <BasePoint> graf;
    std::vector <Infrastructure> infr;
    std::map <std::string, std::vector <Point*> > namePointsMap;
    std::map <unsigned int, Point*> idPointMap;

    // std::map <unsigned int, Infrastructure*> idInfrMap;
    // std::map <unsigned int, BasePoint*> idBasePointsMap;


    void createMapPoints(std::vector <Point*> points);
    void initMaps();
    bool CheckSearchInfo(SearchInfo info);


public:
    // enum class Exeptions { UNKNOWN_POINT };
    Search(DataBase* base);
    bool HavePoint(std::string name);
    SearchInfo CreateSearchInfo(std::string name);
    Route FindRoute(UniqueSearchInfo from, SearchInfo to);
    UniqueSearchInfo CreateUniqueSearchInfo(std::string name);
    bool IsUniquePoint(std::string name);
};