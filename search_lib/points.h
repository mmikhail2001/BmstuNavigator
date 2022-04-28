#pragma once



class Edge {
public:
    unsigned int from;
    unsigned int to;
    unsigned int dist;
    std::string linkToFile;
};

class SearchInfo {
private:
    std::string name;
    unsigned int id;
public:
    std::string GetName() { return name; }
    unsigned int GetId() { return id; }
    SearchInfo(std::string name) : name(name) {}
};

class Point {
public:
    unsigned int id;
    virtual bool IsMe(SearchInfo info) = 0;
    virtual std::vector <Edge> GetWaysToPoint(SearchInfo info) = 0;
    std::vector <Edge> BasePointEdges;
};

class IsGreater {
public:
    bool operator ()(const std::pair <int, Point*> &l, const std::pair <int, Point*> &r) {
        return l.first > r.first;
    }
};

class Infrastructure : public Point {
public:
    std::vector <std::string> names;
    std::vector <Edge> GetWaysToPoint(SearchInfo info) override;
    bool IsMe(SearchInfo info) override;
};

class BasePoint : public Point {
private:
    std::vector <Edge> InfrastructureEdges;
public:
    std::vector <Edge> GetWaysToPoint(SearchInfo info) override;
    bool IsMe(SearchInfo info) override;
};