#include "routingAlgorithmProvider.h"

RoutingAlgorithmProvider::RoutingAlgorithmProvider() {}


RoutingAlgorithm* RoutingAlgorithmProvider::getAlgorithm(
    RoutingType type
    )
{
    switch(type)
    {
        case RoutingType::Random:
            return &random;

        case RoutingType::Flooding:
            return &flooding;

        case RoutingType::Experience:
            return &experience;
    }

    return nullptr;
}

const ExperienceRouting& RoutingAlgorithmProvider::getExperienceRouting() const
{
    return experience;
}

void RoutingAlgorithmProvider::clearExperienceRouting()
{
    experience.clearRoutingTables();
}