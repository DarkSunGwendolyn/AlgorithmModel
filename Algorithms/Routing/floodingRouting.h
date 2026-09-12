#ifndef FLOODINGROUTING_H
#define FLOODINGROUTING_H

#include "routingAlgorithm.h"

class FloodingRouting : public RoutingAlgorithm
{
public:
    QVector<int> getNextVertices(
        const Graph &graph,
        const Packet &packet
        ) override;

};

#endif // FLOODINGROUTING_H
