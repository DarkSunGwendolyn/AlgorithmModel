#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H

#include <QVector>

struct RoutingTable
{
    int vertex;
    QVector<int> distances;
};

#endif // ROUTINGTABLE_H
