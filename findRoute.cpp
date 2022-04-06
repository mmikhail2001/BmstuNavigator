#include <iostream>
#include <vector>
#include <map>

class BasePoint;

class Edge {
public:
    unsigned int vertexTo;
    unsigned int dist;
    std::string linkToFile;
};

class Point {
public:
    unsigned int id;
    std::vector <Edge> BasePointEdges;
};

class Infrastructure : public Point {
public:
    std::string name;
};

class BasePoint : public Point {
public:
    std::vector <Edge> InfrastructureEdges;
};

std::vector <BasePoint> fillTestBasePoints() {
    BasePoint a, b, c;
    a.id = 1;
    // base
    Edge edge = {2, 2, "1->2.txt"};
    a.BasePointEdges.push_back(edge);
    // infr
    edge = {10, 2, "file10.txt"};
    a.InfrastructureEdges.push_back(edge);
    edge = {11, 2, "file11.txt"};
    a.InfrastructureEdges.push_back(edge);


    b.id = 2;
    // base
    edge = {1, 2, ".txt"};
    b.BasePointEdges.push_back(edge);
    edge = {3, 5, ".txt"};
    b.BasePointEdges.push_back(edge);
    // infr
    edge = {10, 0, ".txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {11, 1, ".txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {12, 2, ".txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {13, 3, ".txt"};
    b.InfrastructureEdges.push_back(edge);

    c.id = 3;
    // base
    edge = {1, 2, ".txt"};
    c.BasePointEdges.push_back(edge);
    // infr
    edge = {12, 1, ".txt"};
    c.InfrastructureEdges.push_back(edge);
    edge = {13, 1, ".txt"};
    c.InfrastructureEdges.push_back(edge);

    std::vector <BasePoint> graf = {a, b, c};
    return graf;
}

std:: vector <Infrastructure> fillInfrPoints() {
    Infrastructure i10, i11, i12, i13;
    Edge edge;

    i10.id = 10;
    i10.name = "400u";
    edge = {1, 2, ".txt"};
    i10.BasePointEdges.push_back(edge);
    edge = {2, 0, ".txt"};
    i10.BasePointEdges.push_back(edge);

    i11.id = 11;
    i11.name = "401u";
    edge = {1, 2, ".txt"};
    i11.BasePointEdges.push_back(edge);
    edge = {2, 1, ".txt"};
    i11.BasePointEdges.push_back(edge);

    i12.id = 12;
    i12.name = "402u";
    edge = {2, 2, ".txt"};
    i12.BasePointEdges.push_back(edge);
    edge = {3, 1, ".txt"};
    i12.BasePointEdges.push_back(edge);

    i13.id = 13;
    i13.name = "403u";
    edge = {2, 2, ".txt"};
    i13.BasePointEdges.push_back(edge);
    edge = {3, 1, ".txt"};
    i13.BasePointEdges.push_back(edge);

    std::vector <Infrastructure> graf = {i10, i11, i12, i13};
    return graf;
}

class DataBase {
public:
    std::vector <BasePoint> getBasePoints() {
        return fillTestBasePoints();
    }
    std::vector <Infrastructure> getInfrastructurePoints() {
        return fillInfrPoints();
    }
};

class Search {
    std::vector <BasePoint> graf;
    std::vector <Infrastructure> infr;
    std::map <std::string, unsigned int> map_points;

    void create_map_points() {
        for (auto infrPoint: infr) {
            map_points[infrPoint.name] = infrPoint.id;
        }
    }
    
public:
    Search(DataBase &base) {
        graf = base.getBasePoints();
        infr = base.getInfrastructurePoints();
        create_map_points();
    }
    bool HavePoint(std::string name) {
        return map_points.count(name);
    }
    std::vector <std::string> FindRoute() {
        std::vector <std::string> linksToPhotos;
        
        return linksToPhotos;
    }
};

int main() {
    DataBase data;
    Search s1(data);
    std::cout << s1.HavePoint("501") << std::endl;
    return 0;
}