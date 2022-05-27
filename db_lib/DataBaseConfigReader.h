#ifndef SEARCH_LIB_DATABASECONFIGREADER_H
#define SEARCH_LIB_DATABASECONFIGREADER_H

#include <string>
#include "DataBaseConfig.h"

class DataBaseConfigReader {
public:

    DataBaseConfig readConfig(std::string filePath);

};

#endif //SEARCH_LIB_DATABASECONFIGREADER_H