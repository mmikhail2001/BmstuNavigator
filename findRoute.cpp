#include <iostream>
#include <vector>
#include <map>
#include <queue>

class Point;
class IsGreater {
public:
    bool operator ()(const std::pair <int, Point*> &l, const std::pair <int, Point*> &r) {
        return l.first > r.first;
    }
};

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
    virtual bool IsInfrastucture() { return false; }
    virtual bool IsBasePoint() { return false; }
};

class Infrastructure : public Point {
public:
    std::string name;
    bool IsInfrastucture() override { return true; }
};

class BasePoint : public Point {
public:
    std::vector <Edge> InfrastructureEdges;
    bool IsBasePoint() override { return true; }
};

std::vector <BasePoint> fillTestBasePoints() {
    BasePoint a, b, c, d;
    a.id = 1;
    // base
    Edge edge = {2, 2, "1->2.txt"};
    a.BasePointEdges.push_back(edge);
    edge = {4, 1, ".txt"};
    a.BasePointEdges.push_back(edge);
    // infr
    edge = {9, 5, "file0.txt"};
    a.InfrastructureEdges.push_back(edge);
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
    edge = {2, 5, ".txt"};
    c.BasePointEdges.push_back(edge);
    edge = {4, 2, ".txt"};
    c.BasePointEdges.push_back(edge);
    // infr
    edge = {12, 1, ".txt"};
    c.InfrastructureEdges.push_back(edge);
    edge = {13, 1, ".txt"};
    c.InfrastructureEdges.push_back(edge);

    d.id = 4;
    // base
    edge = {1, 1, "4->1.txt"};
    d.BasePointEdges.push_back(edge);
    edge = {3, 2, "4->3.txt"};
    d.BasePointEdges.push_back(edge);

    std::vector <BasePoint> graf = {a, b, c, d};
    return graf;
}

std::vector <Infrastructure> fillInfrPoints() {
    Infrastructure i9, i10, i11, i12, i13;
    Edge edge;
    i9.id = 9;
    i9.name = "399u";
    edge = {1, 5, ".txt"};
    i9.BasePointEdges.push_back(edge);

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

    std::vector <Infrastructure> graf = {i9, i10, i11, i12, i13};
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
    std::map <std::string, Infrastructure*> nameInfrMap;
    std::map <unsigned int, Infrastructure*> idInfrMap;
    std::map <unsigned int, BasePoint*> idBasePointsMap;
    std::map <Point*, unsigned int> distToPoint;

    void create_map_points() {
        for (int i = 0; i < infr.size(); ++i) {
            nameInfrMap[infr[i].name] = &(infr[i]);
            idInfrMap[infr[i].id] = &(infr[i]);
        }
        for (int i = 0; i < graf.size(); ++i) {
            idBasePointsMap[graf[i].id] = &(graf[i]);
        }
    }

public:
    Search(DataBase &base) {
        graf = base.getBasePoints();
        infr = base.getInfrastructurePoints();
        create_map_points();
    }
    bool HavePoint(std::string name) {
        return nameInfrMap.count(name);
    }
    void show() {
        std::cout << "show: " << std::endl;
        for (int i = 0; i < infr.size(); ++i) {
            std::cout << infr[i].id << std::endl;
        }
    }
    std::vector <std::string> FindRoute(std::string startName, std::string endName) {
        if (!HavePoint(startName) || !HavePoint(endName)) {
            std::cout << "Search->FindRoute start and end must be known\n";
            std::cout << "HERE WILL BE RAISE!\n";
        }
        std::vector <std::string> linksToPhotos;
        std::priority_queue <std::pair<int, Point*>, std::vector <std::pair<int, Point*> >, IsGreater > pq;
        Point* startVertex = nameInfrMap[startName];
        distToPoint[startVertex] = 0;
        pq.push(std::make_pair(0, startVertex));
        int debug = 0;
        while (!pq.empty()) {
            ++debug;
            if (debug > 100) {
                break;
            }
            Point* p = pq.top().second;
            unsigned int dist = pq.top().first;
            std::cout << "dist: " << dist << std::endl;
            std::cout << "id: " << p->id << std::endl;
            pq.pop();
            if (distToPoint[p] < dist) continue;
            for (int i = 0; i < p->BasePointEdges.size(); ++i) {
                // std::cout << (p->BasePointEdges[i]).dist << std::endl;
                unsigned int localDistToPoint = dist + (p->BasePointEdges[i]).dist;
                Point* neighbour = idBasePointsMap[(p->BasePointEdges[i]).vertexTo];
                if (!distToPoint.count(neighbour) || distToPoint[neighbour] > localDistToPoint) {
                    distToPoint[neighbour] = localDistToPoint;
                    pq.push(std::make_pair(localDistToPoint, neighbour));
                }   
            }
            if (p->IsBasePoint()) {
                BasePoint* t = (BasePoint *)p;
                for (int i = 0; i < t->InfrastructureEdges.size(); ++i) {
                    unsigned int localIdInfr = (t->InfrastructureEdges)[i].vertexTo;
                    Infrastructure* localInfr = idInfrMap[localIdInfr];
                    if (idInfrMap[localIdInfr] == nameInfrMap[endName]) {
                        Point* localPoint = (Point*) localInfr;
                        unsigned int localDistToPoint = dist + (t->InfrastructureEdges)[i].dist;
                        if (!distToPoint.count(localPoint) || distToPoint[localPoint] > localDistToPoint) {
                            distToPoint[localPoint] = localDistToPoint;
                        } 
                    }
                }
                // std::cout << "" << t->InfrastructureEdges.size();
                // std::cout << "Id: " << p->id << " ";
                // std::cout << "Is Base Point" << std::endl;
                // pq.push(std::make_pair(p.BasePointEdges));
            }
            // if (p->IsInfrastucture()) {
                // std::cout << "Is Infrastructure" << std::endl;
            // }
        }

        Point* localPoint = nameInfrMap[endName];
        if (!distToPoint.count(localPoint)) {
            std::cout << "We cant find this Route" << std::endl;
        }
        unsigned int dist = distToPoint[localPoint];
        std::cout << " dist to end: " << dist << std::endl;
        return linksToPhotos;
    }
};

int main() {
    DataBase data;
    Search s1(data);
    // s1.show();
    std::cout << s1.HavePoint("501") << std::endl;
    s1.FindRoute("399u", "403u");
    return 0;
}