#pragma once



class Edge {
public:
    unsigned int from;
    unsigned int to;
    unsigned int dist;
    std::string linkToFile;
    // const unsigned int from;
    // const unsigned int to;
    // const unsigned int dist;
    // const std::string linkToFile;
    Edge(const unsigned int from, 
         const unsigned int to,
         const unsigned int dist,
         const std::string linkToFile) : 
         from(from), to(to), dist(dist), linkToFile(linkToFile) {}
};

class SearchInfo {
private:
    std::string name;
public:
    std::string GetName() { return name; }
    SearchInfo(std::string name) : name(name) {}
};


class UniqueSearchInfo : public SearchInfo {
private:
    unsigned int id;

public:
    unsigned int GetId() { return id; }
    UniqueSearchInfo(std::string name, unsigned int id) : SearchInfo(name), id(id) {}
};

class Point {
public:
    unsigned int id;
    std::vector <Edge> BasePointEdges;
    std::vector <std::string> names;

    virtual bool IsMe(SearchInfo info) = 0;
    virtual std::vector <Edge> GetEdgesToNeighbours() = 0;
    void AddBasePointEdge(Edge edge);
    std::vector <std::string> GetNames() { return names; };
    unsigned int GetId() { return id; }

    // may be worth to make one more class with this method
    virtual bool IsPartOfRouteTo(SearchInfo info) = 0;

};



class Infrastructure : public Point {
public:
    std::vector <Edge> GetEdgesToNeighbours() override;
    bool IsMe(SearchInfo info) override;
    bool IsPartOfRouteTo(SearchInfo info) override;
};

class BasePoint : public Point {
public:
    std::vector <Edge> InfrastructureEdges;
    std::vector <Edge> GetEdgesToNeighbours() override;
    bool IsMe(SearchInfo info) override;
    bool IsPartOfRouteTo(SearchInfo info) override;
};