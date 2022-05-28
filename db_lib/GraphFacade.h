#ifndef BMSTUNAVIGATORTEST1_GRAPHFACADE_H
#define BMSTUNAVIGATORTEST1_GRAPHFACADE_H

#include "DataBaseDAO.h"

class GraphFacade {
public:

    GraphFacade() : data(DataBaseDAO::getInstance()) {

    }

    ~GraphFacade() {
        delete data;
    }

    std::vector<BasePoint> getBasePoints();

    std::vector<Infrastructure> getInfrastructurePoints();

private:

    DataBaseDAO *data = nullptr;
};


#endif //BMSTUNAVIGATORTEST1_GRAPHFACADE_H
