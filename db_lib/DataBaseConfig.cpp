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
    if (in.is_open()) {
        /*
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }
         */
        std::string serverTmp;
        std::string userTmp;
        std::string passwordTmp;
        std::string databaseNameTmp;

        getline(in, serverTmp);
        server = serverTmp.c_str();
        getline(in, userTmp);
        user = userTmp.c_str();
        getline(in, passwordTmp);
        password = passwordTmp.c_str();
        getline(in, databaseNameTmp);
        databaseName = databaseNameTmp.c_str();
    } else {
        in.close();
        throw std::runtime_error("Exception. Incorrect path to config file: " + configFilePath + ".");
    }
    //std::cout << server << std::endl;
    //std::cout << user << std::endl;
    //std::cout << password << std::endl;
    //std::cout << databaseName << std::endl;

    in.close();
}
