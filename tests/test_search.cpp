#include <gtest/gtest.h>
#include "search.h"
#include "database.h"
#include "points.h"

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
    edge = {102, 1, "1->canteen.txt"};
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
    // infr
    edge = {103, 1, "4->canteen.txt"};
    d.InfrastructureEdges.push_back(edge);

    std::vector <BasePoint> graf = {a, b, c, d};
    return graf;
}

std::vector <Infrastructure> fillInfrPoints() {
    Infrastructure i9, i10, i11, i12, i13, i102, i103;
    Edge edge;
    i9.id = 9;
    i9.names.push_back("399u");
    edge = {1, 5, "9->1.txt"};
    i9.BasePointEdges.push_back(edge);

    i10.id = 10;
    i10.names.push_back("400u");
    edge = {1, 2, "10->1.txt"};
    i10.BasePointEdges.push_back(edge);
    edge = {2, 0, "10->2.txt"};
    i10.BasePointEdges.push_back(edge);

    i11.id = 11;
    i11.names.push_back("401u");
    edge = {1, 2, "11->1.txt"};
    i11.BasePointEdges.push_back(edge);
    edge = {2, 1, "11->2.txt"};
    i11.BasePointEdges.push_back(edge);

    i12.id = 12;
    i12.names.push_back("402u");
    edge = {2, 2, "12->2.txt"};
    i12.BasePointEdges.push_back(edge);
    edge = {3, 1, "12->3.txt"};
    i12.BasePointEdges.push_back(edge);

    i13.id = 13;
    i13.names.push_back("403u");
    edge = {2, 2, "13->2.txt"};
    i13.BasePointEdges.push_back(edge);
    edge = {3, 1, "13->3.txt"};
    i13.BasePointEdges.push_back(edge);

    i102.id = 102;
    i102.names.push_back("canteen");
    i102.names.push_back("canteen2");
    edge = {1, 1, "canteen->1.txt"};
    i102.BasePointEdges.push_back(edge);

    i103.id = 103;
    i103.names.push_back("canteen");
    i103.names.push_back("canteen3");
    i103.names.push_back("canteen_near_physics");
    edge = {4, 1, "canteen->4.txt"};
    i103.BasePointEdges.push_back(edge);

    std::vector <Infrastructure> graf = {i9, i10, i11, i12, i13, i102, i103};
    return graf;
}


class DataBaseTest : public DataBase {
public:
    std::vector <BasePoint> getBasePoints() override {
        return fillTestBasePoints();
    }
    std::vector <Infrastructure> getInfrastructurePoints() override {
        return fillInfrPoints();
    }
};

TEST(TestCheckExist, test_399u_403u) {
    DataBaseTest data;
    Search s1(&data);
    EXPECT_TRUE(s1.HavePoint("399u"));
    EXPECT_FALSE(s1.HavePoint("have not this infrastructure"));
}


TEST(TestRoute, test_399u_403u) {
    DataBaseTest data;
    Search s1(&data);
    std::vector <std::string> foundRoute = s1.FindRoute("399u", "403u");
    EXPECT_EQ(foundRoute.size(), 4);
    EXPECT_EQ(foundRoute[0], "9->1.txt");
    EXPECT_EQ(foundRoute[1], "1->4.txt");
    EXPECT_EQ(foundRoute[2], "4->3.txt");
    EXPECT_EQ(foundRoute[3], "3->13.txt");
}

TEST(TestRoute, test_401u_403u) {
    DataBaseTest data;
    Search s1(&data);
    std::vector <std::string> foundRoute = s1.FindRoute("401u", "403u");
    EXPECT_EQ(foundRoute.size(), 2);
    EXPECT_EQ(foundRoute[0], "11->2.txt");
    EXPECT_EQ(foundRoute[1], "2->13.txt");
}

TEST(TestRoute, test_401u_401u) {
    DataBaseTest data;
    Search s1(&data);
    std::vector <std::string> foundRoute = s1.FindRoute("401u", "401u");
    EXPECT_EQ(foundRoute.size(), 0);
}

TEST(TestRoute, test_cant_find_object) {
    DataBaseTest data;
    Search s1(&data);
    std::vector <std::string> foundRoute;
    EXPECT_THROW(s1.FindRoute("cant find object", "401u"), std::runtime_error);
}


TEST(TestRoute, find_by_diff_names) {
    DataBaseTest data;
    Search s1(&data);
    std::vector <std::string> foundRoute = s1.FindRoute("399u", "canteen_near_physics");
    EXPECT_EQ(foundRoute.size(), 3);
    EXPECT_EQ(foundRoute[0], "9->1.txt");
    EXPECT_EQ(foundRoute[1], "1->4.txt");
    EXPECT_EQ(foundRoute[2], "4->canteen.txt");

    foundRoute = s1.FindRoute("399u", "canteen3");
    EXPECT_EQ(foundRoute.size(), 3);
    EXPECT_EQ(foundRoute[0], "9->1.txt");
    EXPECT_EQ(foundRoute[1], "1->4.txt");
    EXPECT_EQ(foundRoute[2], "4->canteen.txt");
}

TEST(TestRoute, find_nearest_infr) {
    DataBaseTest data;
    Search s1(&data);
    std::vector <std::string> foundRoute = s1.FindRoute("399u", "canteen");
    EXPECT_EQ(foundRoute.size(), 2);
    EXPECT_EQ(foundRoute[0], "9->1.txt");
    EXPECT_EQ(foundRoute[1], "1->canteen.txt");
}