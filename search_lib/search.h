#pragma once
#include <vector>
#include "points.h"
#include "database.h"


class Route {
    std::vector <Edge> edges;
public:
    void AddEdge(Edge edge) {
        edges.push_back(edge);
    }
    std::vector <Edge> GetEdges() {
        return edges;
    }
    unsigned int Size() {
        return edges.size();
    }
};

class Search {
    struct RoadData {
        unsigned int dist;
        unsigned int indexOfEdge;
        // Point::PointType type;
        Point* prev;
        RoadData() {}
        RoadData(unsigned int getDist, 
                 unsigned int getNumberOfEdge, 
                 Point* getPrev) : 
                 dist(getDist),
                 indexOfEdge(getNumberOfEdge),
                 prev(getPrev){}

    };
    std::vector <BasePoint> graf;
    std::vector <Infrastructure> infr;
    std::map <std::string, Infrastructure*> nameInfrMap;
    std::map <unsigned int, Infrastructure*> idInfrMap;
    std::map <unsigned int, BasePoint*> idBasePointsMap;

    void createMapPoints();

public:
    // enum class Exeptions { UNKNOWN_POINT };
    Search(DataBase* base);
    bool HavePoint(std::string name);
    // SearchInfo CreateSearchInfo(std::string name);
    Route FindRoute(SearchInfo from, SearchInfo to);
};