#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <iterator>
#include <algorithm>
#include <cassert>
#include "points.h"
#include "search.h"
#include "database.h"



void Search::initMaps() {
    std::vector <Point*> vectorOfPtrsToPoints;
    for (auto &point : graf) {
        vectorOfPtrsToPoints.push_back(&point);
    }
    for (auto &point : infr) {
        vectorOfPtrsToPoints.push_back(&point);
    }

    createMapPoints(vectorOfPtrsToPoints);
}

void Search::createMapPoints(std::vector <Point*> ptrsToPoints) {
    for (auto ptrToPoint : ptrsToPoints) {
        std::vector <std::string> names = ptrToPoint->GetNames();
        for (auto name : names) {
            namePointsMap[name].push_back(ptrToPoint);
        }
        idPointMap[ptrToPoint->GetId()] = ptrToPoint;
    }
}


void Search::initDijkstra() {
    for (auto point : graf) {
        for (auto edge : point.GetEdgesToNeighbours()) {
            dijkstraSearcher.AddDirectedEdge(edge.from, edge.to, edge.dist);
        }
    }
    for (auto point : infr) {
        for (auto edge : point.GetEdgesToNeighbours()) {
            dijkstraSearcher.AddDirectedEdge(edge.from, edge.to, edge.dist);
        }
    }
}

Search::Search(DataBase* base) {
    graf = base->getBasePoints();
    infr = base->getInfrastructurePoints();
    initMaps();
    initDijkstra();
}

bool Search::HavePoint(std::string name) {
    return namePointsMap.count(name);
}

Point* Search::getMinPoint(SearchInfo to, std::map <Point*, DistToPointWithEdge > pointWithRoad) {
    std::vector <Point*> points = namePointsMap[to.GetName()];
    Point* minPoint;
    DistToPointWithEdge bestEdge;
    for (auto point : points) {
        if (pointWithRoad[point].dist < bestEdge.dist) {
            minPoint = point;
            bestEdge = pointWithRoad[point];
        }
    }
    return minPoint;
}


Route Search::FindRoute(unsigned int id, std::string name) {
    Route route;
    vector <Point*> points = GetByName(name);
    dijkstraSearcher.FindRoute(id);
    unsigned int dist = dijkstraSearcher.GetDistTo(points[0]->GetId());
    std::cout << "dist is: " << dist << std::endl;
    return route;
}



bool Search::IsUniquePoint(std::string name) {
    if (namePointsMap.count(name) != 1) {
        return false;
    }
    return true;
}

Point* Search::GetById(unsigned int id) {
    return idPointMap[id];
}

vector <Point*> Search::GetByName(std::string name) {
    return namePointsMap[name];
}