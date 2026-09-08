#ifndef PATHMAPPER_H
#define PATHMAPPER_H

#include "floyd.h"
#include "dijkstra.h"
#include "pathTableRow.h"

class PathMapper
{
public:
    static QVector<PathTableRow> map(
        const FloydMatrixResult &result
        );

    static QVector<PathTableRow> map(
        const QVector<QVector<DijkstraResult>>& result
        );
};

#endif // PATHMAPPER_H
