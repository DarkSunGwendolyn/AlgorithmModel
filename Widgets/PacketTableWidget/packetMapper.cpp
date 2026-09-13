#include "packetMapper.h"

PacketTableRow PacketMapper::map(
    const Packet &packet,
    PacketStatus status)
{
    PacketTableRow row;

    row.number = packet.id + 1;

    row.source = packet.source;
    row.destination = packet.destination;

    row.path = packet.route;

    row.size = packet.size;

    row.status = status;

    return row;
}
