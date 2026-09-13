#ifndef VIRTUALCIRCUIT_H
#define VIRTUALCIRCUIT_H

#include "transmissionMethod.h"


class VirtualCircuit : public TransmissionMethod
{
public:
    VirtualCircuit();

    RoutingResult route(
        const Graph &graph,
        const Packet &packet
        ) override;

    void setAlgorithm(RoutingAlgorithm *algorithm) override;

private:
    int virtualCircuitSource = -1;
    int virtualCircuitDestination = -1;

    QVector<int> virtualCircuitRoute;

    RoutingResult movePacketByRoute(
        const Packet &packet
        );

    void clearVirtualCircuit();
};

#endif // VIRTUALCIRCUIT_H
