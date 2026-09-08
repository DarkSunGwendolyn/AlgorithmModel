#include "pathMapper.h"

QVector<PathTableRow> PathMapper::map(
    const FloydMatrixResult &result)
{
    QVector<PathTableRow> rows;

    int n = result.distances.size();

    for (int from = 0; from < n; ++from)
    {
        for (int to = 0; to < n; ++to)
        {
            if (result.distances[from][to] != INT_MAX)
            {
                PathTableRow row;

                row.from = from;
                row.to = to;
                row.path = Floyd::getPath(
                    result,
                    from,
                    to
                );
                row.pathLen = result.distances[from][to];

                rows.append(row);

            }
        }
    }

    return rows;
}

QVector<PathTableRow> PathMapper::map(
    const QVector<QVector<DijkstraResult>> &result)
{
    QVector<PathTableRow> rows;

    int n = result.size();

    for (int from = 0; from < n; ++from)
    {
        for (int to = 0; to < n; ++to)
        {
            if (result[from][to].pathLen != INT_MAX)
            {
                PathTableRow row;

                row.from = from;
                row.to = to;
                row.path = result[from][to].path;
                row.pathLen = result[from][to].pathLen;
                rows.append(row);

            }
        }
    }

    return rows;

}
