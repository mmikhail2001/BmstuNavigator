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
    // optional<vector <unsigned int>> optRoad;

    if (road.size() == 0) {
        return optRoute;
    }

    for (int i = 0; i < ((int)road.size()) - 1; ++i) {
        route.AddEdge(GetById(road[i])->GetEdgeById(road[i + 1]));
    }
    optRoute = route;
    return optRoute;


    // DEBUG:
    // std::cout << "THIS IS RESULTED ROAD:" << endl;
    // for (auto edge : route) {
    //     std::cout << edge.linkToFile << " ";
    // }
    // std::copy(road.begin(), road.end(), 
    //             std::ostream_iterator<unsigned int> (std::cout, " "));

    // unsigned int dist = dijkstraSearcher.GetDistTo(minPoint->GetId());
    // std::cout << "dist is: " << dist << std::endl;
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