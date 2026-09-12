#ifndef PACKET_H
#define PACKET_H

#include <QVector>

#include "transmissionType.h"

struct Packet
{
    int id;
    int source;
    int destination;
    int size;

    int currentVertex;
    int previousVertex;

    int ttl;

    TransmissionType transmissionType;


    QVector<int> route;
};

#endif // PACKET_H