#ifndef ROUTINGALGORITHMPROVIDER_H
#define ROUTINGALGORITHMPROVIDER_H

#include "routingType.h"
#include "randomRouting.h"
#include "floodingRouting.h"

class RoutingAlgorithmProvider
{
public:
    RoutingAlgorithmProvider();

    RoutingAlgorithm* getAlgorithm(RoutingType type);

private:
    RandomRouting random;
    FloodingRouting flooding;
};

#endif // ROUTINGALGORITHMPROVIDER_H
