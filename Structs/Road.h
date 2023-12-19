#ifndef HOWTOGETTHERE_ROAD_H
#define HOWTOGETTHERE_ROAD_H

#include "Coordinates.h"

struct road {
    int cost = 0;
    coordinates previous = { -1, -1 };
    coordinates current = { -1, -1 };
};

#endif //HOWTOGETTHERE_ROAD_H
