#ifndef RANDOMROUTING_H
#define RANDOMROUTING_H

#include <QRandomGenerator>

#include "routingAlgorithm.h"

class RandomRouting : public RoutingAlgorithm
{
public:

    QVector<int> getNextVertices(
        const Graph &graph,
        const Packet &packet
        ) override;


};

#endif // RANDOMROUTING_H
