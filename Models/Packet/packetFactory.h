#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include "packet.h"

class PacketFactory
{
public:

    static Packet create(
        int source,
        int destination,
        int size,
        int ttl,
        TransmissionType transmission
        );

    static void reset();

private:

    static int nextPacketId;

};

#endif // PACKETFACTORY_H
