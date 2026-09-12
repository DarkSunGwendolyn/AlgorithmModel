#include "randomRouting.h"

QVector<int> RandomRouting::getNextVertices(
    const Graph &graph,
    const Packet &packet
    )
{
    QVector<int> nextVertices;

    for (const Edge& edge : graph.getEdges())
    {
        if (edge.from == packet.currentVertex)
        {
            nextVertices.append(edge.to);
        }
    }

    if (nextVertices.isEmpty())
    {
        return {};
    }

    int idx = QRandomGenerator::global()->bounded(nextVertices.size());

    return {nextVertices[idx]};
}
