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


void Search::create_map_points() {
    for (int i = 0; i < infr.size(); ++i) {
        nameInfrMap[infr[i].name] = &(infr[i]);
        idInfrMap[infr[i].id] = &(infr[i]);
    }
    for (int i = 0; i < graf.size(); ++i) {
        idBasePointsMap[graf[i].id] = &(graf[i]);
    }
}

Search::Search(DataBase* base) {
    graf = base->getBasePoints();
    infr = base->getInfrastructurePoints();
    create_map_points();
}

bool Search::HavePoint(std::string name) {
    return nameInfrMap.count(name);
}

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
        // std::cout << "dist: " << dist << std::endl;
        // std::cout << "id: " << p->id << std::endl;
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


void showRoute(std::vector <std::string> foundRoute) {
    std::cout << "links: " << std::endl;
    for (auto link : foundRoute) {
        std::cout << link << std::endl;
    }
}
/*

int main() {
    // DataBase data;
    // Search s1(data);
    // s1.show();
    // std::cout << s1.HavePoint("501") << std::endl;
    // s1.FindRoute("399u", "403u");
    return 0;
}
*/