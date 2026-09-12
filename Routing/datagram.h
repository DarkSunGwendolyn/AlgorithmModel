#ifndef DATAGRAM_H
#define DATAGRAM_H

#include "transmissionMethod.h"

class Datagram : public TransmissionMethod
{
public:
    Datagram();

    RoutingResult route(
        const Graph &graph,
        const Packet &packet
        ) override;
};

#endif // DARAGRAM_H
