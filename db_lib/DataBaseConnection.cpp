#include <iostream>
#include "DataBaseConnection.h"

DataBaseConnection::DataBaseConnection(DataBaseConfig *dataBaseConfig) : connection(
        mysqlConnectionSetup(dataBaseConfig)) {

}

MYSQL *DataBaseConnection::mysqlConnectionSetup(DataBaseConfig *dataBaseConfig) {
    MYSQL *connection = mysql_init(nullptr); // mysql instance

    //connect database
    if (!mysql_real_connect(connection, dataBaseConfig->server, dataBaseConfig->user, dataBaseConfig->password,
                            dataBaseConfig->databaseName, 0, nullptr, 0)) {
        std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }

    return connection;
}

DataBaseConnection::~DataBaseConnection() {
    // Close database connection
    mysql_close(connection);
}
