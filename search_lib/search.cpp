#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <optional>
#include "points.h"
#include "search.h"
#include "database.h"

using std::cout;
using std::endl;
using std::optional;
using std::vector;
using std::string;

void Search::initMaps() {
    vector <Point*> vectorOfPtrsToPoints;
    for (auto &point : graf) {
        vectorOfPtrsToPoints.push_back(&point);
    }
    for (auto &point : infr) {
        vectorOfPtrsToPoints.push_back(&point);
    }

    createMapPoints(vectorOfPtrsToPoints);
}

void Search::createMapPoints(vector <Point*> ptrsToPoints) {
    for (auto ptrToPoint : ptrsToPoints) {
        vector <string> names = ptrToPoint->GetNames();
        for (auto name : names) {
            namePointsMap[name].push_back(ptrToPoint);
        }
        idPointMap[ptrToPoint->GetId()] = ptrToPoint;
    }
}


void Search::initDijkstra() {
    for (auto point : graf) {
        for (auto edge : point.GetEdges()) {
            dijkstraSearcher.AddDirectedEdge(edge.from, edge.to, edge.dist);
        }
    }
    for (auto point : infr) {
        for (auto edge : point.GetEdges()) {
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



optional <Route> Search::FindRoute(unsigned int id, std::string name) {
    Route route;
    optional <Route> optRoute;
    vector <Point*> points = GetByName(name);
    if (!idPointMap.count(id)) {
        return optRoute;
    }
    dijkstraSearcher.FindRoute(id);
    unsigned int minDist;
    Point* minPoint = nullptr;
    for (auto point : points) {
        optional <unsigned int> dist = dijkstraSearcher.GetDistTo(point->GetId());
        if (!minPoint || (dist && *dist < minDist)) {
            minPoint = point;
            minDist = *dist;
        }
    }
    
    if (!minPoint) {
        return optRoute;
    }

    vector <unsigned int> road = dijkstraSearcher.GetRoadTo(minPoint->GetId());

    if (road.size() == 0) {
        return optRoute;
    }

    for (int i = 0; i < ((int)road.size()) - 1; ++i) {
        route.AddEdge(GetById(road[i])->GetEdgeById(road[i + 1]));
    }
    optRoute = route;
    return optRoute;

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