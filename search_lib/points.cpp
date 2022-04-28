#include <vector>
#include <string>
#include "points.h"


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

std::vector <Edge> BasePoint::GetWaysToPoint(SearchInfo info) {
    std::vector <Edge> neighbours = BasePointEdges;
    for (auto edge : InfrastructureEdges) {
        if (edge.to == info.GetId()) {
            neighbours.push_back(edge);
        }
    }
    return neighbours;
}

std::vector <Edge> Infrastructure::GetWaysToPoint(SearchInfo info) {
    return BasePointEdges;
}