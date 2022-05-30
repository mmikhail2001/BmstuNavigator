#include <gtest/gtest.h>

TEST(test_tools, test_true_1) {

    EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// std::vector <BasePoint> fillTestBasePoints() {
//     BasePoint a(1), b(2), c(3), d(4);
//     // base
//     {
//         Edge edge(1, 2, 2, "1->2.txt");
//         a.AddEdge(edge);
//     }
//     {
//         Edge edge(1, 4, 1, "1->4.txt");
//         a.AddEdge(edge);
//     }
//     // infr
//     {
//         Edge edge(1, 9, 5, "1->9.txt");
//         a.AddEdge(edge);
//     }
//     {
//         Edge edge(1, 10, 2, "1->10.txt");
//         a.AddEdge(edge);
//     }
//     {
//         Edge edge(1, 11, 2, "1->11.txt");
//         a.AddEdge(edge);
//     }
//     {
//         Edge edge(1, 102, 1, "1->canteen.txt");
//         a.AddEdge(edge);
//     }

//     // base
//     {
//         Edge edge(2, 1, 2, "2->1.txt");
//         b.AddEdge(edge);
//     }
//     {
//         Edge edge(2, 3, 5, "2->3.txt");
//         b.AddEdge(edge);
//     }
//     // infr
//     {
//         Edge edge(2, 10, 0, "2->10.txt");
//         b.AddEdge(edge);
//     }
//     {
//         Edge edge(2, 11, 1, "2->11.txt");
//         b.AddEdge(edge);
//     }
//     {
//         Edge edge(2, 12, 2, "2->12.txt");
//         b.AddEdge(edge);
//     }
//     {
//         Edge edge(2, 13, 3, "2->13.txt");
//         b.AddEdge(edge);
//     }

//     // base
//     {
//         Edge edge(3, 2, 5, "3->2.txt");
//         c.AddEdge(edge);
//     }
//     {
//         Edge edge(3, 4, 2, "3->4.txt");
//         c.AddEdge(edge);
//     }
//     // infr
//     {
//         Edge edge(3, 12, 1, "3->12.txt");
//         c.AddEdge(edge);
//     }
//     {
//         Edge edge(3, 13, 1, "3->13.txt");
//         c.AddEdge(edge);
//     }

//     // base
//     {
//         Edge edge(d.GetId(), 1, 1, "4->1.txt");
//         d.AddEdge(edge);
//     }
//     {
//         Edge edge(d.GetId(), 3, 2, "4->3.txt");
//         d.AddEdge(edge);
//     }
//     // infr
//     {
//         Edge edge(d.GetId(), 103, 1, "4->canteen.txt");
//         d.AddEdge(edge);
//     }

//     std::vector <BasePoint> graf = {a, b, c, d};
//     return graf;
// }

// std::vector <Infrastructure> fillInfrPoints() {
//     Infrastructure i9(9), i10(10), i11(11), i12(12), i13(13), i102(102), i103(103);

//     i9.AddName("399u");
//     {
//         Edge edge(i9.GetId(), 1, 5, "9->1.txt");
//         i9.AddEdge(edge);
//     }

//     i10.AddName("400u");
//     {
//         Edge edge(i10.GetId(), 1, 2, "10->1.txt");
//         i10.AddEdge(edge);
//     }
//     {
//         Edge edge(i10.GetId(), 2, 0, "10->2.txt");
//         i10.AddEdge(edge);
//     }

//     i11.AddName("401u");
//     {
//         Edge edge(i11.GetId(), 1, 2, "11->1.txt");
//         i11.AddEdge(edge);
//     }
//     {
//         Edge edge(i11.GetId(), 2, 1, "11->2.txt");
//         i11.AddEdge(edge);
//     }

//     i12.AddName("402u");
//     {
//         Edge edge(i12.GetId(), 2, 2, "12->2.txt");
//         i12.AddEdge(edge);
//     }
//     {
//         Edge edge(i12.GetId(), 3, 1, "12->3.txt");
//         i12.AddEdge(edge);
//     }

//     i13.AddName("403u");
//     {
//         Edge edge(i13.GetId(), 2, 2, "13->2.txt");
//         i13.AddEdge(edge);
//     }
//     {
//         Edge edge(i13.GetId(), 3, 1, "13->3.txt");
//         i13.AddEdge(edge);
//     }

//     i102.AddName("canteen");
//     i102.AddName("canteen2");
//     {
//         Edge edge(i102.GetId(), 1, 1, "canteen->1.txt");
//         i102.AddEdge(edge);
//     }

//     i103.AddName("canteen");
//     i103.AddName("canteen3");
//     i103.AddName("canteen_near_physics");
//     {
//         Edge edge(i103.GetId(), 4, 1, "canteen->4.txt");
//         i103.AddEdge(edge);
//     }

//     std::vector <Infrastructure> graf = {i9, i10, i11, i12, i13, i102, i103};
//     return graf;
// }


// class DataBaseTest : public DataBase {
// public:
//     std::vector <BasePoint> getBasePoints() override {
//         return fillTestBasePoints();
//     }
//     std::vector <Infrastructure> getInfrastructurePoints() override {
//         return fillInfrPoints();
//     }
// };

// TEST(TestCheckExist, test_399u_403u) {
//     DataBaseTest data;
//     Search s1(&data);
//     EXPECT_TRUE(s1.HavePoint("399u"));
//     EXPECT_FALSE(s1.HavePoint("have not this infrastructure"));
// }


// TEST(TestRoute, test_399u_403u) {
//     DataBaseTest data;
//     Search s1(&data);
//     vector <Point*> from = s1.GetByName("399u");
//     unsigned int id = from[0]->GetId();
//     Route route = s1.FindRoute(id, "403u");
//     ASSERT_EQ(route.Size(), 4);
//     std::vector <Edge> foundRoute = route.GetEdges();
//     EXPECT_EQ(foundRoute[0].linkToFile, "9->1.txt");
//     EXPECT_EQ(foundRoute[1].linkToFile, "1->4.txt");
//     EXPECT_EQ(foundRoute[2].linkToFile, "4->3.txt");
//     EXPECT_EQ(foundRoute[3].linkToFile, "3->13.txt");
// }

// TEST(TestRoute, test_401u_403u) {
//     DataBaseTest data;
//     Search s1(&data);

//     vector <Point*> from = s1.GetByName("401u");
//     unsigned int id = from[0]->GetId();
//     Route route = s1.FindRoute(id, "403u");
    
//     std::vector <Edge> foundRoute = route.GetEdges();

//     ASSERT_EQ(foundRoute.size(), 2);
//     EXPECT_EQ(foundRoute[0].linkToFile, "11->2.txt");
//     EXPECT_EQ(foundRoute[1].linkToFile, "2->13.txt");
// }

// TEST(TestRoute, test_401u_401u) {
//     DataBaseTest data;
//     Search s1(&data);

//     vector <Point*> from = s1.GetByName("401u");
//     unsigned int id = from[0]->GetId();
//     Route route = s1.FindRoute(id, "401u");

//     EXPECT_EQ(route.Size(), 0);
// }

// /*
// TEST(TestRoute, test_cant_find_object) {
//     DataBaseTest data;
//     Search s1(&data);

//     EXPECT_THROW(s1.CreateUniqueSearchInfo("cant find object"), std::runtime_error);
//     UniqueSearchInfo from("cant find object", 0);
//     SearchInfo to = s1.CreateSearchInfo("401u");

//     // TODO: DELETE THIS
//     ASSERT_EQ(1, 0);
//     EXPECT_THROW(s1.FindRoute(from, to), std::runtime_error);
// }
// */


// TEST(TestRoute, find_by_diff_names) {
//     DataBaseTest data;
//     Search s1(&data);
    
//     vector <Point*> from = s1.GetByName("399u");
//     unsigned int id = from[0]->GetId();
//     Route route = s1.FindRoute(id, "canteen_near_physics");

//     std::vector <Edge> foundRoute = route.GetEdges();

//     ASSERT_EQ(foundRoute.size(), 3);
//     EXPECT_EQ(foundRoute[0].linkToFile, "9->1.txt");
//     EXPECT_EQ(foundRoute[1].linkToFile, "1->4.txt");
//     EXPECT_EQ(foundRoute[2].linkToFile, "4->canteen.txt");

//     from = s1.GetByName("399u");
//     id = from[0]->GetId();
//     route = s1.FindRoute(id, "canteen3");

//     foundRoute = route.GetEdges();

//     ASSERT_EQ(foundRoute.size(), 3);
//     EXPECT_EQ(foundRoute[0].linkToFile, "9->1.txt");
//     EXPECT_EQ(foundRoute[1].linkToFile, "1->4.txt");
//     EXPECT_EQ(foundRoute[2].linkToFile, "4->canteen.txt");
// }

// TEST(TestRoute, find_nearest_infr) {
//     DataBaseTest data;
//     Search s1(&data);

//     vector <Point*> from = s1.GetByName("399u");
//     unsigned int id = from[0]->GetId();
//     Route route = s1.FindRoute(id, "canteen");

//     std::vector <Edge> foundRoute = route.GetEdges();

//     ASSERT_EQ(foundRoute.size(), 2);
//     EXPECT_EQ(foundRoute[0].linkToFile, "9->1.txt");
//     EXPECT_EQ(foundRoute[1].linkToFile, "1->canteen.txt");
// }