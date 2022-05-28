#ifndef SEARCH_LIB_DATABASECONFIG_H
#define SEARCH_LIB_DATABASECONFIG_H

#include <string>

class DataBaseConfig {
public:
    DataBaseConfig(const char *server, const char *user, const char *password, const char *databaseName);

    DataBaseConfig(const std::string &configFilePath);

    ~DataBaseConfig();

    const char *server;

    const char *user;

    const char *password;

    const char *databaseName;

private:

    void readConfigFile(const std::string &configFilePath);
};

#endif //SEARCH_LIB_DATABASECONFIG_H