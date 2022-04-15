#pragma once
#include <vector>
#include "points.h"
#include "database.h"


class Search {
    struct RoadData {
        unsigned int dist;
        unsigned int indexOfEdge;
        Point::PointType type;
        Point* prev;
        RoadData() {}
        RoadData(unsigned int getDist, 
                 unsigned int getNumberOfEdge, 
                 Point* getPrev, 
                 Point::PointType getType = Point::PointType::BasePoint) : 
                 dist(getDist),
                 indexOfEdge(getNumberOfEdge),
                 prev(getPrev),
                 type(getType) {}

    };
    std::vector <BasePoint> graf;
    std::vector <Infrastructure> infr;
    std::map <std::string, Infrastructure*> nameInfrMap;
    std::map <unsigned int, Infrastructure*> idInfrMap;
    std::map <unsigned int, BasePoint*> idBasePointsMap;

    void create_map_points();

public:
    enum class Exeptions { UNKNOWN_POINT };
    Search(DataBase* base);
    bool HavePoint(std::string name);
    std::vector <std::string> FindRoute(std::string startName, std::string endName);
};