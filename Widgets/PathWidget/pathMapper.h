#ifndef PATHMAPPER_H
#define PATHMAPPER_H

#include "floyd.h"
#include "pathWidget.h"

class PathMapper
{
public:
    static QVector<PathTableRow> map(
        const FloydMatrixResult &result
        );
};

#endif // PATHMAPPER_H
