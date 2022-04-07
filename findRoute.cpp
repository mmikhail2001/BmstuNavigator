#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <iterator>
#include <algorithm>
#include <cassert>

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
    enum class PointType { Infrastructure, BasePoint };
    unsigned int id;
    std::vector <Edge> BasePointEdges;
    virtual PointType Type() = 0;
};

class Infrastructure : public Point {
public:
    std::string name;
    PointType Type() override { return PointType::Infrastructure; }
};

class BasePoint : public Point {
public:
    std::vector <Edge> InfrastructureEdges;
    PointType Type() override { return PointType::BasePoint; }
};

std::vector <BasePoint> fillTestBasePoints() {
    BasePoint a, b, c, d;
    Edge edge;
    a.id = 1;
    // base
    edge = {2, 2, "1->2.txt"};
    a.BasePointEdges.push_back(edge);
    edge = {4, 1, "1->4.txt"};
    a.BasePointEdges.push_back(edge);
    // infr
    edge = {9, 5, "1->9.txt"};
    a.InfrastructureEdges.push_back(edge);
    edge = {10, 2, "1->10.txt"};
    a.InfrastructureEdges.push_back(edge);
    edge = {11, 2, "1->11.txt"};
    a.InfrastructureEdges.push_back(edge);


    b.id = 2;
    // base
    edge = {1, 2, "2->1.txt"};
    b.BasePointEdges.push_back(edge);
    edge = {3, 5, "2->3.txt"};
    b.BasePointEdges.push_back(edge);
    // infr
    edge = {10, 0, "2->10.txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {11, 1, "2->11.txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {12, 2, "2->12.txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {13, 3, "2->13.txt"};
    b.InfrastructureEdges.push_back(edge);

    c.id = 3;
    // base
    edge = {2, 5, "3->2.txt"};
    c.BasePointEdges.push_back(edge);
    edge = {4, 2, "3->4.txt"};
    c.BasePointEdges.push_back(edge);
    // infr
    edge = {12, 1, "3->12.txt"};
    c.InfrastructureEdges.push_back(edge);
    edge = {13, 1, "3->13.txt"};
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
    edge = {1, 5, "9->1.txt"};
    i9.BasePointEdges.push_back(edge);

    i10.id = 10;
    i10.name = "400u";
    edge = {1, 2, "10->1.txt"};
    i10.BasePointEdges.push_back(edge);
    edge = {2, 0, "10->2.txt"};
    i10.BasePointEdges.push_back(edge);

    i11.id = 11;
    i11.name = "401u";
    edge = {1, 2, "11->1.txt"};
    i11.BasePointEdges.push_back(edge);
    edge = {2, 1, "11->2.txt"};
    i11.BasePointEdges.push_back(edge);

    i12.id = 12;
    i12.name = "402u";
    edge = {2, 2, "12->2.txt"};
    i12.BasePointEdges.push_back(edge);
    edge = {3, 1, "12->3.txt"};
    i12.BasePointEdges.push_back(edge);

    i13.id = 13;
    i13.name = "403u";
    edge = {2, 2, "13->2.txt"};
    i13.BasePointEdges.push_back(edge);
    edge = {3, 1, "13->3.txt"};
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
    struct OptimalDistData {
        unsigned int dist;
        unsigned int indexOfEdge;
        Point::PointType type;
        Point* prev;
        OptimalDistData() {}
        OptimalDistData(unsigned int getDist, 
                        unsigned int getNumberOfEdge, 
                        Point* getPrev, 
                        Point::PointType getType = Point::PointType::BasePoint) : dist(getDist),
                        indexOfEdge(getNumberOfEdge),
                        prev(getPrev),
                        type(getType) {}

    };
    std::vector <BasePoint> graf;
    std::vector <Infrastructure> infr;
    std::map <std::string, Infrastructure*> nameInfrMap;
    std::map <unsigned int, Infrastructure*> idInfrMap;
    std::map <unsigned int, BasePoint*> idBasePointsMap;

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
        std::vector <std::string> linksToFiles;
        std::priority_queue <std::pair<int, Point*>, std::vector <std::pair<int, Point*> >, IsGreater > pq;
        std::map <Point*, OptimalDistData > distToPoint;
        Point* startVertex = nameInfrMap[startName];
        OptimalDistData optDataFirst(0, 0, NULL);
        distToPoint[startVertex] = optDataFirst;
        pq.push(std::make_pair(0, startVertex));
        while (!pq.empty()) {
            Point* p = pq.top().second;
            unsigned int dist = pq.top().first;
            // std::cout << "dist: " << dist << std::endl;
            // std::cout << "id: " << p->id << std::endl;
            pq.pop();
            if (distToPoint[p].dist < dist) continue;
            for (int i = 0; i < p->BasePointEdges.size(); ++i) {
                unsigned int localDistToPoint = dist + (p->BasePointEdges[i]).dist;
                Point* neighbour = idBasePointsMap[(p->BasePointEdges[i]).vertexTo];
                if (!distToPoint.count(neighbour) || distToPoint[neighbour].dist > localDistToPoint) {
                    OptimalDistData optData(localDistToPoint, i, p);
                    distToPoint[neighbour] = optData;
                    pq.push(std::make_pair(localDistToPoint, neighbour));
                }
            }
            if (p->Type() == Point::PointType::BasePoint) {
                BasePoint* bpPtr = (BasePoint *)p;
                for (int i = 0; i < bpPtr->InfrastructureEdges.size(); ++i) {
                    unsigned int localIdInfr = (bpPtr->InfrastructureEdges)[i].vertexTo;
                    Infrastructure* localInfr = idInfrMap[localIdInfr];
                    if (idInfrMap[localIdInfr] == nameInfrMap[endName]) {
                        Point* localPoint = (Point*) localInfr;
                        unsigned int localDistToPoint = dist + (bpPtr->InfrastructureEdges)[i].dist;
                        if (!distToPoint.count(localPoint) || distToPoint[localPoint].dist > localDistToPoint) {
                            OptimalDistData optData(localDistToPoint, i, p, Point::PointType::Infrastructure);
                            distToPoint[localPoint] = optData;
                        } 
                    }
                }
            }
        }

        Point* localPoint = nameInfrMap[endName];
        if (!distToPoint.count(localPoint)) {
            std::cout << "We cant find this Route" << std::endl;
            return linksToFiles;
        }
        unsigned int dist = distToPoint[localPoint].dist;
        OptimalDistData optData = distToPoint[localPoint];
        while (true) {
            Point* ptr = optData.prev;
            if (ptr == NULL) break;
            if (optData.type == Point::PointType::Infrastructure) {
                BasePoint* bpPtr = (BasePoint*)ptr;
                linksToFiles.push_back((bpPtr->InfrastructureEdges)[optData.indexOfEdge].linkToFile);
            } else {
                linksToFiles.push_back((ptr->BasePointEdges)[optData.indexOfEdge].linkToFile);
            }
            optData = distToPoint[ptr];
        }
        std::reverse(linksToFiles.begin(), linksToFiles.end());
        std::cout << " dist to end: " << dist << std::endl;
        return linksToFiles;
    }
};


void showRoute(std::vector <std::string> foundRoute) {
    std::cout << "links: " << std::endl;
    for (auto link : foundRoute) {
        std::cout << link << std::endl;
    }
}

void test() {
    DataBase data;
    Search s1(data);
    {
        std::vector <std::string> foundRoute = s1.FindRoute("399u", "403u");
        assert(foundRoute.size() == 4);
        assert(foundRoute[0] == "9->1.txt");
        assert(foundRoute[1] == "1->4.txt");
        assert(foundRoute[2] == "4->3.txt");
        assert(foundRoute[3] == "3->13.txt");
    }
    {
        std::vector <std::string> foundRoute = s1.FindRoute("401u", "403u");
        assert(foundRoute.size() == 2);
        assert(foundRoute[0] == "11->2.txt");
        assert(foundRoute[1] == "2->13.txt");
    }
    {
        std::vector <std::string> foundRoute = s1.FindRoute("401u", "401u");
        assert(foundRoute.size() == 0);
    }

}

int main() {
    test();
    // DataBase data;
    // Search s1(data);
    // s1.show();
    // std::cout << s1.HavePoint("501") << std::endl;
    // s1.FindRoute("399u", "403u");
    return 0;
}