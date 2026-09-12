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
    }

    return nullptr;
}