#ifndef ROUTINGALGORITHMPROVIDER_H
#define ROUTINGALGORITHMPROVIDER_H

#include "routingType.h"
#include "randomRouting.h"
#include "floodingRouting.h"
#include "experienceRouting.h"

class RoutingAlgorithmProvider
{
public:
    RoutingAlgorithmProvider();

    RoutingAlgorithm* getAlgorithm(RoutingType type);

    const ExperienceRouting& getExperienceRouting() const;

    void clearExperienceRouting();

private:
    RandomRouting random;
    FloodingRouting flooding;
    ExperienceRouting experience;
};

#endif // ROUTINGALGORITHMPROVIDER_H
