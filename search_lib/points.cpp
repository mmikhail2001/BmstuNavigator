#include <vector>
#include <string>
#include "points.h"

Point::PointType Infrastructure::Type() { return Point::PointType::Infrastructure; }

Point::PointType BasePoint::Type() { return Point::PointType::BasePoint; }