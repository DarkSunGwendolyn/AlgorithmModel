#include "packetFactory.h"

int PacketFactory::nextPacketId = 0;

Packet PacketFactory::create(
    int source,
    int destination,
    int size,
    int ttl,
    TransmissionType type
    )
{
    Packet packet;

    packet.id = nextPacketId++;

    packet.source = source;
    packet.destination = destination;

    packet.currentVertex = source;
    packet.previousVertex = -1;

    packet.size = size;

    packet.ttl = ttl;

    packet.transmissionType = type;

    packet.route.append(source);

    return packet;
}

void PacketFactory::reset()
{
    nextPacketId = 0;
}
