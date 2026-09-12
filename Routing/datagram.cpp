#include "datagram.h"

Datagram::Datagram()
{

}

RoutingResult Datagram::route(
    const Graph &graph,
    const Packet &packet
    )
{
    return TransmissionMethod::route(graph, packet);
}
