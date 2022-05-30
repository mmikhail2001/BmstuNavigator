#ifndef BMSTUNAVIGATORTEST1_GRAPHFACADE_H
#define BMSTUNAVIGATORTEST1_GRAPHFACADE_H

#include "DataBaseDAO.h"
#include "database.h"

class GraphFacade : public DataBase {
public:

    GraphFacade() : data(DataBaseDAO::getInstance()) {

    }

    ~GraphFacade() {
        delete data;
    }

    std::vector<BasePoint> getBasePoints() override;

    std::vector<Infrastructure> getInfrastructurePoints() override;

private:

    DataBase *data = nullptr;
};


#endif //BMSTUNAVIGATORTEST1_GRAPHFACADE_H

