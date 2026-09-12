#ifndef ROUTINGRESULT_H
#define ROUTINGRESULT_H

#include "packet.h"

struct RoutingResult
{
    QVector<Packet> packets;
    QVector<Packet> deliveredPackets;
    QVector<Packet> expiredPackets;
};

#endif // ROUTINGRESULT_H
