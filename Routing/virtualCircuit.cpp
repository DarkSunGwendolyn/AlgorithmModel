#include "virtualCircuit.h"

VirtualCircuit::VirtualCircuit()
{

}

RoutingResult VirtualCircuit::route(
    const Graph &graph,
    const Packet &packet)
{
    RoutingResult result;

    if (virtualCircuitSource != packet.source ||
        virtualCircuitDestination != packet.destination)
    {
        clearVirtualCircuit();

        virtualCircuitSource = packet.source;
        virtualCircuitDestination = packet.destination;
    }

    if (virtualCircuitRoute.isEmpty())
    {
        RoutingResult result =
            TransmissionMethod::route(graph, packet);

        if (!result.deliveredPackets.isEmpty())
        {
            virtualCircuitRoute =
                result.deliveredPackets.first().route;
        }

        return result;
    }

    return movePacketByRoute(packet);
}

void VirtualCircuit::buildRoute(
    const Graph &graph,
    const Packet &packet)
{
    QVector<Packet> activePackets;
    activePackets.append(packet);

    while(!activePackets.isEmpty())
    {
        QVector<Packet> nextPackets;
        for (const Packet &activePacket : activePackets)
        {
            RoutingResult stepResult =
                movePacket(graph, activePacket);

            if (!stepResult.deliveredPackets.isEmpty())
            {
                virtualCircuitRoute =
                    stepResult.deliveredPackets.first().route;
            }

            nextPackets += stepResult.packets;
        }

        activePackets = nextPackets;
    }
}

RoutingResult VirtualCircuit::movePacketByRoute(
    const Packet &packet)
{
    RoutingResult result;

    if (virtualCircuitRoute.isEmpty())
    {
        return result;
    }

    Packet routedPacket = packet;
    routedPacket.route = virtualCircuitRoute;

    routedPacket.currentVertex =
        virtualCircuitRoute.first();

    if (virtualCircuitRoute.last() != routedPacket.destination)
    {
        result.expiredPackets.append(routedPacket);
        return result;
    }

    routedPacket.currentVertex =
        virtualCircuitRoute.last();

    routedPacket.ttl -=
        virtualCircuitRoute.size() - 1;

    if (routedPacket.ttl >= 0)
    {
        result.deliveredPackets.append(routedPacket);
    }
    else
    {
        result.expiredPackets.append(routedPacket);
    }

    return result;
}

void VirtualCircuit::setAlgorithm(RoutingAlgorithm *algorithm)
{
    if (this->getAlgorithm() != algorithm)
    {
        clearVirtualCircuit();
    }

    TransmissionMethod::setAlgorithm(algorithm);
}

void VirtualCircuit::clearVirtualCircuit()
{
    virtualCircuitRoute.clear();

    virtualCircuitSource = -1;
    virtualCircuitDestination = -1;
}
