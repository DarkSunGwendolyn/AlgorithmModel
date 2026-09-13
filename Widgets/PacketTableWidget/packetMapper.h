#ifndef PACKETMAPPER_H
#define PACKETMAPPER_H

#include "packet.h"
#include "packetStatus.h"
#include "packetTableRow.h"

class PacketMapper
{
public:
    static PacketTableRow map(
        const Packet &packet,
        PacketStatus status
        );
};

#endif // PACKETMAPPER_H
