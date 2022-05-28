#ifndef SEARCH_LIB_DATABASECONNECTION_H
#define SEARCH_LIB_DATABASECONNECTION_H

#include "DataBaseConfig.h"
#include <mysql.h>

class DataBaseConnection {
public:

    explicit DataBaseConnection(DataBaseConfig *dataBaseConfig);

    ~DataBaseConnection();

    MYSQL *connection;	// The connection

private:

    MYSQL* mysqlConnectionSetup(DataBaseConfig *dataBaseConfig);

};

#endif //SEARCH_LIB_DATABASECONNECTION_H