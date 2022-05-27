#pragma once
#include <iostream>
#include <vector>
#include "points.h"

class DataBase {
public:
    virtual std::vector <BasePoint> getBasePoints() = 0;
    virtual std::vector <Infrastructure> getInfrastructurePoints() = 0;
};