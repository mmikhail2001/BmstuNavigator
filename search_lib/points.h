#pragma once



class Edge {
public:
    const unsigned int from;
    const unsigned int to;
    const unsigned int dist;
    const std::string linkToFile;
    Edge(const unsigned int from, 
         const unsigned int to,
         const unsigned int dist,
         const std::string linkToFile) : 
         from(from), to(to), dist(dist), linkToFile(linkToFile) {}
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
    void AddBasePointEdge(Edge edge);
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
public:
    std::vector <Edge> InfrastructureEdges;
    std::vector <Edge> GetWaysToPoint(SearchInfo info) override;
    bool IsMe(SearchInfo info) override;
};