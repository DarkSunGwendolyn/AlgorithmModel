#ifndef TRANSMISSIONMETHOD_H
#define TRANSMISSIONMETHOD_H

#include "routingAlgorithm.h"
#include "routingResult.h"

class TransmissionMethod
{
public:
    TransmissionMethod();

    virtual RoutingResult route(
        const Graph &graph,
        const Packet &packet
        );

    virtual void setAlgorithm(RoutingAlgorithm *algorithm);

    RoutingAlgorithm* getAlgorithm();

protected:
    RoutingResult movePacket(
        const Graph &graph,
        const Packet &packet);


private:
    RoutingAlgorithm *algorithm = nullptr;
};

#endif // TRANSMISSIONMETHOD_H
