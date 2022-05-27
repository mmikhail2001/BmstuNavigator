#include "DataBaseConfig.h"
#include <iostream>
#include <fstream>

DataBaseConfig::DataBaseConfig(const char *server, const char *user, const char *password, const char *databaseName)
        : server(server), user(user), password(password), databaseName(databaseName) {

}

DataBaseConfig::DataBaseConfig(const std::string &configFilePath) {
    // TODO read and initialize data from the config file path
    readConfigFile(configFilePath);
}

DataBaseConfig::~DataBaseConfig() {
    delete server;
    delete user;
    delete password;
    delete databaseName;
}

void DataBaseConfig::readConfigFile(const std::string &configFilePath) {
    std::string line;

    std::ifstream in(configFilePath);
    if (in.is_open())
    {
        /*
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }
         */
        getline(in, line);
        server = &line[0];
        getline(in, line);
        user = &line[0];
        getline(in, line);
        password = &line[0];
        getline(in, line);
        databaseName = &line[0];
    }

    in.close();
}
