#ifndef PACKETROUTER_H
#define PACKETROUTER_H

#include "datagram.h"
#include "virtualCircuit.h"

class PacketRouter
{
public:
    PacketRouter();

    RoutingResult routePacket(
        const Graph &graph,
        const Packet &packet
        );

    void setRoutingAlgorithm(
        RoutingAlgorithm *algorithm
        );


private:
    Datagram datagram;
    VirtualCircuit virtualCircuit;
};

#endif // PACKETROUTER_H
