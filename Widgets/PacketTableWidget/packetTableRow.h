#ifndef PACKETTABLEROW_H
#define PACKETTABLEROW_H

#include <QVector>
#include "packetStatus.h"

struct PacketTableRow
{
    int number;

    int source;
    int destination;

    QVector<int> path;

    int size;

    PacketStatus status;

};

#endif // PACKETTABLEROW_H
