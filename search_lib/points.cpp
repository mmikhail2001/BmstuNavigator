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
