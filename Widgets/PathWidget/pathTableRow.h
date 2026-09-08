#ifndef PATHTABLEROW_H
#define PATHTABLEROW_H

#include <QVector>

struct PathTableRow
{
    int from;
    int to;
    QVector<int> path;
    int pathLen;
};

#endif // PATHTABLEROW_H