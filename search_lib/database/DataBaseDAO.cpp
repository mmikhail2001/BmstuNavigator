#include "DataBaseDAO.h"
#include "DataBaseConfigReader.h"

DataBaseDAO *DataBaseDAO::dataBaseDao = nullptr;;

DataBaseDAO *DataBaseDAO::GetInstance() {
    if (dataBaseDao == nullptr) {
        dataBaseDao = new DataBaseDAO();
        DataBaseConfigReader dataBaseConfigReader;
        dataBaseDao->dataBaseConnection = DataBaseConnection(dataBaseConfigReader.readConfig("config.txt"));
    }

    return dataBaseDao;
}

std::vector<BasePoint> DataBaseDAO::getBasePoints() {
    std::vector<BasePoint> vector = {};
    return vector;
}

std::vector<Infrastructure> DataBaseDAO::getInfrastructurePoints() {
    std::vector<Infrastructure> vector = {};
    return vector;
}

BasePoint DataBaseDAO::getBasePoint(unsigned int id) {
    // TODO
    return BasePoint();
};

unsigned int DataBaseDAO::addBasePoint(BasePoint basePoint) {
    // TODO
    return 0;
}

bool DataBaseDAO::updateBasePoint(BasePoint basePoint) {
    // TODO
    return false;
}

bool DataBaseDAO::removeBasePoint(unsigned int id) {
    // TODO
    return false;
}

Infrastructure DataBaseDAO::getInfrastructure(unsigned int id) {
    // TODO
    return Infrastructure();
}

unsigned int DataBaseDAO::addInfrastructure(Infrastructure infrastructure) {
    // TODO
    return 0;
}

bool DataBaseDAO::updateInfrastructure(Infrastructure infrastructure) {
    // TODO
    return false;
}

bool DataBaseDAO::removeInfrastructure(unsigned int id) {
    // TODO
    return false;
}

Edge DataBaseDAO::getEdge(unsigned int id) {
    // TODO
    return Edge();
}

unsigned int DataBaseDAO::addEdge(Edge edge) {
    // TODO
    return 0;
}

bool DataBaseDAO::updateEdge(Edge edge) {
    // TODO
    return false;
}

bool DataBaseDAO::removeEdge(unsigned int id) {
    // TODO
    return false;
}

User DataBaseDAO::getUserByLoginPassword(std::string login, std::string password) {
    // TODO
    return User();
}
