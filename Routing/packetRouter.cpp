#include "packetRouter.h"

PacketRouter::PacketRouter(){}

RoutingResult PacketRouter::routePacket(
    const Graph &graph,
    const Packet &packet)
{
    if (packet.transmissionType ==
        TransmissionType::Datagram)
    {
       return datagram.route(graph, packet);
    }

    return virtualCircuit.route(graph, packet);
}

void PacketRouter::setRoutingAlgorithm(
    RoutingAlgorithm *algorithm
    )
{
    datagram.setAlgorithm(algorithm);
    virtualCircuit.setAlgorithm(algorithm);
}
