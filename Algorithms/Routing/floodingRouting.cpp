#include "floodingRouting.h"

QVector<int> FloodingRouting::getNextVertices(
    const Graph &graph,
    const Packet &packet)
{
    QVector<int> nextVertices;

    for (const Edge &edge: graph.getEdges())
    {
        if (edge.from == packet.currentVertex &&
            edge.to != packet.previousVertex)
        {
            nextVertices.append(edge.to);
        }
    }

    return nextVertices;
}
