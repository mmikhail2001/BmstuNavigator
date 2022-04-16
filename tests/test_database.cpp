#include <gtest/gtest.h>
#include "search.h"
#include "DataBaseConfigReader.h"
#include "DataBaseDAO.h"


TEST(TestDataBaseConfigReader, readConfig) {
DataBaseConfigReader dataBaseConfigReader;
DataBaseConfig dataBaseConfig = dataBaseConfigReader.readConfig("config.txt");
std::string connectionURL = ""; // TODO
std::string login = ""; // TODO
std::string password = ""; // TODO
EXPECT_EQ(dataBaseConfig.connectionURL, connectionURL);
EXPECT_EQ(dataBaseConfig.login, login);
EXPECT_EQ(dataBaseConfig.password, password);
}

TEST(TestDataBaseDAO, getBasePoint) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
int id = 123;
BasePoint basePoint = dataBaseDao->getBasePoint(id);
EXPECT_EQ(basePoint.id, id);
}

TEST(TestDataBaseDAO, addBasePoint) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
BasePoint basePoint;
basePoint.id = 33;
unsigned int id = dataBaseDao->addBasePoint(basePoint);
EXPECT_EQ(id, 33);
}

TEST(TestDataBaseDAO, updateBasePoint) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
BasePoint basePoint;
bool res = dataBaseDao->updateBasePoint(basePoint);
EXPECT_EQ(res, true);
}


TEST(TestDataBaseDAO, removeBasePoint) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
BasePoint basePoint;
basePoint.id = 33;
unsigned int id = dataBaseDao->addBasePoint(basePoint);
bool res = dataBaseDao->removeBasePoint(id);
EXPECT_EQ(res, true);
}

TEST(TestDataBaseDAO, getInfrastructure) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
int id = 123;
Infrastructure infrastructure = dataBaseDao->getInfrastructure(id);
EXPECT_EQ(infrastructure.id, id);
}

TEST(TestDataBaseDAO, addInfrastructure) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
Infrastructure infrastructure;
infrastructure.id = 33;
unsigned int id = dataBaseDao->addInfrastructure(infrastructure);
EXPECT_EQ(id, 33);
}

TEST(TestDataBaseDAO, updateInfrastructure) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
Infrastructure infrastructure;
bool res = dataBaseDao->updateInfrastructure(infrastructure);
EXPECT_EQ(res, true);
}


TEST(TestDataBaseDAO, removeInfrastructure) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
Infrastructure infrastructure;
infrastructure.id = 33;
unsigned int id = dataBaseDao->addInfrastructure(infrastructure);
bool res = dataBaseDao->removeInfrastructure(id);
EXPECT_EQ(res, true);
}

TEST(TestDataBaseDAO, getEdge) {
// TODO
}

TEST(TestDataBaseDAO, addEdge) {
// TODO
}

TEST(TestDataBaseDAO, updateEdge) {
// TODO
}

TEST(TestDataBaseDAO, removeEdge) {
// TODO
}

TEST(TestDataBaseDAO, getUserByLoginPassword) {
DataBaseDAO* dataBaseDao = DataBaseDAO::getInstance();
std::string login = "qwerty";
std::string password = "asd";
User user = dataBaseDao->getUserByLoginPassword(login, password);
EXPECT_EQ(user.login, login);
EXPECT_EQ(user.password, password);
}