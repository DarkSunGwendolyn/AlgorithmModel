#ifndef ROUTINGALGORITHM_H
#define ROUTINGALGORITHM_H

#include "graph.h"
#include "packet.h"

class RoutingAlgorithm
{
public:

    virtual QVector<int> getNextVertices(
        const Graph &graph,
        const Packet &packet
        ) = 0;
};

#endif // ROUTINGALGORITHM_H
