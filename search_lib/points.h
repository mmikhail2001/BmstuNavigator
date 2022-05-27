#pragma once
#include <map>



class Edge {
public:
    unsigned int from;
    unsigned int to;
    unsigned int dist;
    std::string linkToFile;
    Edge() : from(0), to(0), dist(0) {}
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



class Point {
    std::map <unsigned int, Edge> idPointMap;
    unsigned int id;
    std::vector <Edge> Edges;
    std::vector <std::string> names;
    
public:
    Point(unsigned int id) : id(id) {}
    void AddName(std::string name);
    std::vector <std::string> GetNames() { return names; };

    void AddEdge(Edge edge);
    std::vector <Edge> GetEdges();

    unsigned int GetId() { return id; }
    Edge GetEdgeById(const unsigned int& id);

};



class Infrastructure : public Point {
public:
    Infrastructure(const unsigned int id) : Point(id) {}
};

class BasePoint : public Point {
public:
    BasePoint(const unsigned int id) : Point(id) {}
};