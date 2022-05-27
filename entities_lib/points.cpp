#include <vector>
#include <string>
#include "points.h"


void Point::AddName(std::string name) {
    names.push_back(name);
}

Edge Point::GetEdgeById(const unsigned int& id) {
    return idPointMap[id];
}


std::vector <Edge> Point::GetEdges() {
    return Edges;
}

void Point::AddEdge(Edge edge) {
    Edges.push_back(edge);
    idPointMap[edge.to] = edge;
}




/*
std::vector <Edge> BasePoint::GetEdgesToNeighbours() {
    std::vector <Edge> neighbours = BasePointEdges;
    for (auto edge : InfrastructureEdges) {
        neighbours.push_back(edge);
    }
    return neighbours;
}
*/

/*
std::vector <Edge> Infrastructure::GetEdgesToNeighbours() {
    return BasePointEdges;
}
*/

/*
bool Infrastructure::IsPartOfRouteTo(SearchInfo info) {
    std::string myName = info.GetName();
    for (auto name : names) {
        if (myName == name) {
            return true;
        }
    }
    return false;
}
*/


/*
bool BasePoint::IsPartOfRouteTo(SearchInfo info) {
    return true;
}
*/