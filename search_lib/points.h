#pragma once



class Edge {
public:
    unsigned int vertexTo;
    unsigned int dist;
    std::string linkToFile;
};

class Point {
public:
    enum class PointType { Infrastructure, BasePoint };
    unsigned int id;
    std::vector <Edge> BasePointEdges;
    virtual PointType Type() = 0;
};

class IsGreater {
public:
    bool operator ()(const std::pair <int, Point*> &l, const std::pair <int, Point*> &r) {
        return l.first > r.first;
    }
};

class Infrastructure : public Point {
public:
    std::string name;
    PointType Type() override;
};

class BasePoint : public Point {
public:
    std::vector <Edge> InfrastructureEdges;
    PointType Type() override;
};