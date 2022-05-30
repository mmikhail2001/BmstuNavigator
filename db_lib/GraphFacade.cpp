#include "GraphFacade.h"

std::vector<BasePoint> GraphFacade::getBasePoints() {
    return data->getBasePoints();
}

std::vector<Infrastructure> GraphFacade::getInfrastructurePoints() {
    return data->getInfrastructurePoints();
}
