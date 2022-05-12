#include <gtest/gtest.h>
#include "search.h"
#include "database.h"
#include "points.h"


std::vector <BasePoint> fillTestBasePoints() {
    BasePoint a, b, c, d;
    a.id = 1;
    // base
    {
        Edge edge(1, 2, 2, "1->2.txt");
        a.AddBasePointEdge(edge);
    }
    {
        Edge edge(1, 4, 1, "1->4.txt");
        a.AddBasePointEdge(edge);
    }
    // infr
    {
        Edge edge(1, 9, 5, "1->9.txt");
        a.InfrastructureEdges.push_back(edge);
    }
    {
        Edge edge(1, 10, 2, "1->10.txt");
        a.InfrastructureEdges.push_back(edge);
    }
    {
        Edge edge(1, 11, 2, "1->11.txt");
        a.InfrastructureEdges.push_back(edge);
    }
    {
        Edge edge(1, 102, 1, "1->canteen.txt");
        a.InfrastructureEdges.push_back(edge);
    }

    b.id = 2;
    // base
    {
        Edge edge(2, 1, 2, "2->1.txt");
        b.AddBasePointEdge(edge);
    }
    {
        Edge edge(2, 3, 5, "2->3.txt");
        b.AddBasePointEdge(edge);
    }
    // infr
    {
        Edge edge(2, 10, 0, "2->10.txt");
        b.InfrastructureEdges.push_back(edge);
    }
    {
        Edge edge(2, 11, 1, "2->11.txt");
        b.InfrastructureEdges.push_back(edge);
    }
    {
        Edge edge(2, 12, 2, "2->12.txt");
        b.InfrastructureEdges.push_back(edge);
    }
    {
        Edge edge(2, 13, 3, "2->13.txt");
        b.InfrastructureEdges.push_back(edge);
    }

    c.id = 3;
    // base
    {
        Edge edge(3, 2, 5, "3->2.txt");
        c.AddBasePointEdge(edge);
    }
    {
        Edge edge(3, 4, 2, "3->4.txt");
        c.AddBasePointEdge(edge);
    }
    // infr
    {
        Edge edge(3, 12, 1, "3->12.txt");
        c.InfrastructureEdges.push_back(edge);
    }
    {
        Edge edge(3, 13, 1, "3->13.txt");
        c.InfrastructureEdges.push_back(edge);
    }

    d.id = 4;
    // base
    {
        Edge edge(d.id, 1, 1, "4->1.txt");
        d.AddBasePointEdge(edge);
    }
    {
        Edge edge(d.id, 3, 2, "4->3.txt");
        d.AddBasePointEdge(edge);
    }
    // infr
    {
        Edge edge(d.id, 103, 1, "4->canteen.txt");
        d.InfrastructureEdges.push_back(edge);
    }

    std::vector <BasePoint> graf = {a, b, c, d};
    return graf;
}

std::vector <Infrastructure> fillInfrPoints() {
    Infrastructure i9, i10, i11, i12, i13, i102, i103;
    i9.id = 9;
    i9.names.push_back("399u");
    {
        Edge edge(i9.id, 1, 5, "9->1.txt");
        i9.AddBasePointEdge(edge);
    }

    i10.id = 10;
    i10.names.push_back("400u");
    {
        Edge edge(i10.id, 1, 2, "10->1.txt");
        i10.AddBasePointEdge(edge);
    }
    {
        Edge edge(i10.id, 2, 0, "10->2.txt");
        i10.AddBasePointEdge(edge);
    }

    i11.id = 11;
    i11.names.push_back("401u");
    {
        Edge edge(i11.id, 1, 2, "11->1.txt");
        i11.AddBasePointEdge(edge);
    }
    {
        Edge edge(i11.id, 2, 1, "11->2.txt");
        i11.AddBasePointEdge(edge);
    }

    i12.id = 12;
    i12.names.push_back("402u");
    {
        Edge edge(i12.id, 2, 2, "12->2.txt");
        i12.AddBasePointEdge(edge);
    }
    {
        Edge edge(i12.id, 3, 1, "12->3.txt");
        i12.AddBasePointEdge(edge);
    }

    i13.id = 13;
    i13.names.push_back("403u");
    {
        Edge edge(i13.id, 2, 2, "13->2.txt");
        i13.AddBasePointEdge(edge);
    }
    {
        Edge edge(i13.id, 3, 1, "13->3.txt");
        i13.AddBasePointEdge(edge);
    }

    i102.id = 102;
    i102.names.push_back("canteen");
    i102.names.push_back("canteen2");
    {
        Edge edge(i102.id, 1, 1, "canteen->1.txt");
        i102.AddBasePointEdge(edge);
    }

    i103.id = 103;
    i103.names.push_back("canteen");
    i103.names.push_back("canteen3");
    i103.names.push_back("canteen_near_physics");
    {
        Edge edge(i103.id, 4, 1, "canteen->4.txt");
        i103.BasePointEdges.push_back(edge);
    }

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
    vector <Point*> from = s1.GetByName("399u");
    // vector <Point*> to = s1.GetByN("403u");
    Route route = s1.FindRoute(from[0]->id, "403u");
    ASSERT_EQ(route.Size(), 4);
    std::vector <Edge> foundRoute = route.GetEdges();
    EXPECT_EQ(foundRoute[0].linkToFile, "9->1.txt");
    EXPECT_EQ(foundRoute[1].linkToFile, "1->4.txt");
    EXPECT_EQ(foundRoute[2].linkToFile, "4->3.txt");
    EXPECT_EQ(foundRoute[3].linkToFile, "3->13.txt");
}
/*
TEST(TestRoute, test_401u_403u) {
    DataBaseTest data;
    Search s1(&data);

    UniqueSearchInfo from = s1.CreateUniqueSearchInfo("401u");
    SearchInfo to = s1.CreateSearchInfo("403u");
    Route route = s1.FindRoute(from, to);
    std::vector <Edge> foundRoute = route.GetEdges();

    ASSERT_EQ(foundRoute.size(), 2);
    EXPECT_EQ(foundRoute[0].linkToFile, "11->2.txt");
    EXPECT_EQ(foundRoute[1].linkToFile, "2->13.txt");
}

TEST(TestRoute, test_401u_401u) {
    DataBaseTest data;
    Search s1(&data);
    UniqueSearchInfo from = s1.CreateUniqueSearchInfo("401u");
    SearchInfo to = s1.CreateSearchInfo("401u");
    Route route = s1.FindRoute(from, to);
    EXPECT_EQ(route.Size(), 0);
}

TEST(TestRoute, test_cant_find_object) {
    DataBaseTest data;
    Search s1(&data);

    EXPECT_THROW(s1.CreateUniqueSearchInfo("cant find object"), std::runtime_error);
    UniqueSearchInfo from("cant find object", 0);
    SearchInfo to = s1.CreateSearchInfo("401u");

    // TODO: DELETE THIS
    ASSERT_EQ(1, 0);
    EXPECT_THROW(s1.FindRoute(from, to), std::runtime_error);
}


TEST(TestRoute, find_by_diff_names) {
    DataBaseTest data;
    Search s1(&data);

    UniqueSearchInfo from = s1.CreateUniqueSearchInfo("399u");
    SearchInfo to = s1.CreateSearchInfo("canteen_near_physics");
    Route route = s1.FindRoute(from, to);
    std::vector <Edge> foundRoute = route.GetEdges();

    ASSERT_EQ(foundRoute.size(), 3);
    EXPECT_EQ(foundRoute[0].linkToFile, "9->1.txt");
    EXPECT_EQ(foundRoute[1].linkToFile, "1->4.txt");
    EXPECT_EQ(foundRoute[2].linkToFile, "4->canteen.txt");

    from = s1.CreateUniqueSearchInfo("399u");
    to = s1.CreateSearchInfo("canteen3");
    route = s1.FindRoute(from, to);
    foundRoute = route.GetEdges();

    ASSERT_EQ(foundRoute.size(), 3);
    EXPECT_EQ(foundRoute[0].linkToFile, "9->1.txt");
    EXPECT_EQ(foundRoute[1].linkToFile, "1->4.txt");
    EXPECT_EQ(foundRoute[2].linkToFile, "4->canteen.txt");
}

TEST(TestRoute, find_nearest_infr) {
    DataBaseTest data;
    Search s1(&data);

    UniqueSearchInfo from = s1.CreateUniqueSearchInfo("399u");
    SearchInfo to = s1.CreateSearchInfo("canteen");
    Route route = s1.FindRoute(from, to);
    std::vector <Edge> foundRoute = route.GetEdges();

    ASSERT_EQ(foundRoute.size(), 2);
    EXPECT_EQ(foundRoute[0].linkToFile, "9->1.txt");
    EXPECT_EQ(foundRoute[1].linkToFile, "1->canteen.txt");
}*/