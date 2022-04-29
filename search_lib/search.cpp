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

Search::Search(DataBase* base) {
    graf = base->getBasePoints();
    infr = base->getInfrastructurePoints();
    initMaps();
}

bool Search::HavePoint(std::string name) {
    return namePointsMap.count(name);
}



Route Search::FindRoute(UniqueSearchInfo from, SearchInfo to) {
    // TODO: check valid
    // if (!CheckSearchInfo(from) || !CheckSearchInfo(to)) {
    //     throw std::runtime_error("ERROR: SEARCH->FindRoute: SearchInfo was not found!");
    // }

    Route route;

    std::priority_queue <DistToPointWithPoint, std::vector <DistToPointWithPoint>, IsGreater > pq;
    std::map <Point*, DistToPointWithEdge > pointWithRoad;
    Point* start = idPointMap[from.GetId()];

    DistToPointWithPoint distAndPoint(0, start);
    DistToPointWithEdge distAndEdge;
    pointWithRoad[start] = distAndEdge;
    pq.push(distAndPoint);
    while (!pq.empty()) {
        // std::cout << "." << std::endl;
        Point* point = pq.top().point;
        unsigned int dist = pq.top().dist;

        pq.pop();

        // if we already found better road to this point we need to skip iteration
        if (pointWithRoad.count(point) && pointWithRoad[point].dist < dist) continue;

        for (auto edge : point->GetEdgesToNeighbours()) {
            // std::cout << "In" << std::endl;
            int distToNext = dist + edge.dist;
            Point* nextPoint = idPointMap[edge.to];

            // skip if this is point cant be a part of route
            if (!nextPoint->IsPartOfRouteTo(to)) {
                continue;
            }

            if (pointWithRoad.count(nextPoint) == 0 || pointWithRoad[nextPoint].dist > distToNext) {
                DistToPointWithPoint distAndNextPoint(distToNext, nextPoint);
                pq.push(distAndNextPoint);

                DistToPointWithEdge distAndEdgeToNext(distToNext, edge);
                pointWithRoad[nextPoint] = distAndEdgeToNext;
            }
        }
    }

    // TODO: WE WANT TO UNDERSTAND THE ID ONLY AT THE END!
    // Point* end = idPointMap[to.GetId()];


    // std::cout << "dist from: " << from.GetName() << " " << " to: " << to.GetName();
    // std::cout << " is: " << pointWithRoad[end].dist << std::endl;


    // restablish route
    // unsigned int idOfPoint = to.GetId();
    // while (true) {
    //     if (idOfPoint == from.GetId()) {
    //         break;
    //     }
    //     Point* pointOfWay = idPointMap[idOfPoint];
    //     Edge tmpEdge = pointWithRoad[pointOfWay].edge;
    //     idOfPoint = tmpEdge.from;
    //     route.AddEdge(tmpEdge);
    // }
    // route.Reverse();
    return route;
}

/*
std::vector <std::string> Search::FindRoute(std::string startName, std::string endName) {
    if (!HavePoint(startName) || !HavePoint(endName)) {
        // std::cout << "ERROR: Search->FindRoute: unknown point was obtained" << std::endl;
        throw std::runtime_error("ERROR: Search->FindRoute: unknown point was obtained");
    }
    std::vector <std::string> linksToFiles;
    std::priority_queue <std::pair<int, Point*>, std::vector <std::pair<int, Point*> >, IsGreater > pq;
    std::map <Point*, RoadData > distToPoint;
    Point* startVertex = nameInfrMap[startName];
    RoadData optDataFirst(0, 0, NULL);
    distToPoint[startVertex] = optDataFirst;
    pq.push(std::make_pair(0, startVertex));
    while (!pq.empty()) {
        Point* p = pq.top().second;
        unsigned int dist = pq.top().first;
        pq.pop();
        if (distToPoint[p].dist < dist) continue;
        for (int i = 0; i < p->BasePointEdges.size(); ++i) {
            unsigned int localDistToPoint = dist + (p->BasePointEdges[i]).dist;
            Point* neighbour = idBasePointsMap[(p->BasePointEdges[i]).vertexTo];
            if (!distToPoint.count(neighbour) || distToPoint[neighbour].dist > localDistToPoint) {
                RoadData optData(localDistToPoint, i, p);
                distToPoint[neighbour] = optData;
                pq.push(std::make_pair(localDistToPoint, neighbour));
            }
        }
        if (p->Type() == Point::PointType::BasePoint) {
            BasePoint* bpPtr = (BasePoint *)p;
            for (int i = 0; i < bpPtr->InfrastructureEdges.size(); ++i) {
                unsigned int localIdInfr = (bpPtr->InfrastructureEdges)[i].vertexTo;
                Infrastructure* localInfr = idInfrMap[localIdInfr];
                if (idInfrMap[localIdInfr] == nameInfrMap[endName]) {
                    Point* localPoint = (Point*) localInfr;
                    unsigned int localDistToPoint = dist + (bpPtr->InfrastructureEdges)[i].dist;
                    if (!distToPoint.count(localPoint) || distToPoint[localPoint].dist > localDistToPoint) {
                        RoadData optData(localDistToPoint, i, p, Point::PointType::Infrastructure);
                        distToPoint[localPoint] = optData;
                    }
                }
            }
        }
    }

    Point* localPoint = nameInfrMap[endName];
    if (!distToPoint.count(localPoint)) {
        throw std::runtime_error("ERROR: We cant find this Route");
    }
    unsigned int dist = distToPoint[localPoint].dist;
    RoadData optData = distToPoint[localPoint];
    while (true) {
        Point* ptr = optData.prev;
        if (ptr == NULL) break;
        if (optData.type == Point::PointType::Infrastructure) {
            BasePoint* bpPtr = (BasePoint*)ptr;
            linksToFiles.push_back((bpPtr->InfrastructureEdges)[optData.indexOfEdge].linkToFile);
        } else {
            linksToFiles.push_back((ptr->BasePointEdges)[optData.indexOfEdge].linkToFile);
        }
        optData = distToPoint[ptr];
    }
    std::reverse(linksToFiles.begin(), linksToFiles.end());
    // std::cout << " dist to end: " << dist << std::endl;
    return linksToFiles;
}

*/




SearchInfo Search::CreateSearchInfo(std::string name) {
    if (namePointsMap.count(name) == 0) {
        throw std::runtime_error("ERROR: SEARCH->CreateSearchInfo: name was not found!");
    }
    SearchInfo info(name);//nameInfrMap[name]->id);
    return info;
}



bool Search::CheckSearchInfo(SearchInfo info) {
    return HavePoint(info.GetName());
}


bool Search::IsUniquePoint(std::string name) {
    if (namePointsMap.count(name) != 1) {
        return false;
    }
    return true;
}

UniqueSearchInfo Search::CreateUniqueSearchInfo(std::string name) {
    if (!IsUniquePoint(name)) {
        throw std::runtime_error("ERROR: SEARCH->CreateUniqueSearchInfo:"); 
    }
    Point* pointPtr = namePointsMap[name][0];
    if (pointPtr == nullptr) {
        throw std::runtime_error("ERROR: SEARCH->CreateUniqueSearchInfo: nullptr found"); 
    }
    UniqueSearchInfo info(name, pointPtr->GetId());
    return info;
}
