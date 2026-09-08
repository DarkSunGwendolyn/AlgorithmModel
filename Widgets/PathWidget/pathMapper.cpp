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
