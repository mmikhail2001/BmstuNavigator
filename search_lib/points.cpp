#include <vector>
#include <string>
#include "points.h"

void Point::AddBasePointEdge(Edge edge) {
    BasePointEdges.push_back(edge);
}

bool Infrastructure::IsMe(SearchInfo info) {
    for (auto name : names) {
        if (info.GetName() == name) {
            return true;
        }
    }
    return false;
}

bool BasePoint::IsMe(SearchInfo info) {
    return false;
}

std::vector <Edge> BasePoint::GetEdgesToNeighbours() {
    std::vector <Edge> neighbours = BasePointEdges;
    for (auto edge : InfrastructureEdges) {
        neighbours.push_back(edge);
    }
    return neighbours;
}

std::vector <Edge> Infrastructure::GetEdgesToNeighbours() {
    return BasePointEdges;
}


bool Infrastructure::IsPartOfRouteTo(SearchInfo info) {
    std::string myName = info.GetName();
    for (auto name : names) {
        if (myName == name) {
            return true;
        }
    }
    return false;
}

bool BasePoint::IsPartOfRouteTo(SearchInfo info) {
    return true;
}