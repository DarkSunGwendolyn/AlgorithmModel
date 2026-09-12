#include "transmissionMethod.h"

TransmissionMethod::TransmissionMethod()
{

}


RoutingResult TransmissionMethod::route(
    const Graph &graph,
    const Packet &packet
    )
{
    RoutingResult result;
    QVector<Packet> activePackets;

    activePackets.append(packet);

    while (!activePackets.isEmpty())
    {
        QVector<Packet> nextPackets;

        for (const Packet &packet : activePackets)
        {
            RoutingResult stepResult =
                movePacket(graph, packet);

            result.deliveredPackets += stepResult.deliveredPackets;
            result.expiredPackets += stepResult.expiredPackets;
            nextPackets += stepResult.packets;
        }

        activePackets = nextPackets;
    }

    return result;
}

RoutingResult TransmissionMethod::movePacket(
    const Graph &graph,
    const Packet &packet)
{
    RoutingResult result;

    QVector<int> nextVertices =
        algorithm->getNextVertices(graph, packet);

    if (nextVertices.isEmpty())
    {
        result.expiredPackets.append(packet);
        return result;
    }

    for (int nextVertex : nextVertices)
    {
        Packet nextPacket = packet;

        nextPacket.previousVertex = packet.currentVertex;
        nextPacket.currentVertex = nextVertex;
        nextPacket.ttl--;
        nextPacket.route.append(nextVertex);

        if (nextVertex == nextPacket.destination)
        {
            result.deliveredPackets.append(nextPacket);
        }
        else if (nextPacket.ttl > 0)
        {
            result.packets.append(nextPacket);
        }
        else
        {
            result.expiredPackets.append(nextPacket);
        }
    }

    return result;
}

RoutingAlgorithm* TransmissionMethod::getAlgorithm()
{
    return algorithm;
}

void TransmissionMethod::setAlgorithm(RoutingAlgorithm *algorithm)
{
    this->algorithm = algorithm;
}