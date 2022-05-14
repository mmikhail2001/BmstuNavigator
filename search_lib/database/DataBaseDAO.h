#ifndef SEARCH_LIB_DATABASEDAO_H
#define SEARCH_LIB_DATABASEDAO_H

#include "../database.h"
#include "DataBaseConnection.h"
#include "../entities/User.h"

class DataBaseDAO : public DataBase {
private:
    // Singleton pattern
    DataBaseDAO() {
    }

    // Singleton pattern
    static DataBaseDAO *dataBaseDao;

    static DataBaseConnection *dataBaseConnection;

    MYSQL_RES *performQuery(const char *sqlQuery);

public:

    ~DataBaseDAO();

    // Singleton should not be cloneable
    DataBaseDAO(DataBaseDAO &other) = delete;

    // Singleton should not be assignable
    void operator=(const DataBaseDAO &) = delete;

    static DataBaseDAO *getInstance();

    std::vector<BasePoint> getBasePoints() override;

    std::vector<Infrastructure> getInfrastructurePoints() override;

    BasePoint getBasePoint(unsigned int id);

    unsigned int addBasePoint(BasePoint basePoint);

    bool updateBasePoint(BasePoint basePoint);

    bool removeBasePoint(unsigned int id);

    Infrastructure getInfrastructure(unsigned int id);

    unsigned int addInfrastructure(Infrastructure infrastructure);

    bool updateInfrastructure(Infrastructure infrastructure);

    bool removeInfrastructure(unsigned int id);

    Edge getEdge(unsigned int id);

    unsigned int addEdge(Edge edge);

    bool updateEdge(Edge edge);

    bool removeEdge(unsigned int id);

    User getUserByLoginPassword(std::string login, std::string password);

};

#endif //SEARCH_LIB_DATABASEDAO_H