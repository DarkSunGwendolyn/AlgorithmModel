#include "floyd.h"


FloydResult Floyd::findShortestPath(
    const Graph &graph,
    int start,
    int finish
    )
{
    FloydMatrixResult mResult =
        findShortestPaths(graph);

    if (mResult.negativeCycle)
    {
        return {
            {},
            INT_MAX,
            true
            };
    }

    if (mResult.distances[start][finish] == INT_MAX)
    {
        return {
            {},
            INT_MAX,
            false
        };
    }

    QVector<int> path =
        buildPath(mResult.theta, start, finish);

    return {
        path,
        mResult.distances[start][finish],
        false
    };
}

FloydMatrixResult Floyd::findShortestPaths(
    const Graph& graph
    )
{
    QVector<QVector<int>> matrix =
        graph.getAdjacencyMatrix();

    int n = matrix.size();

    QVector<QVector<int>> distances = initializeDistances(matrix);

    QVector<QVector<int>> theta = initializeTheta(matrix);

    for (int k = 0; k < n; ++k)
    {
        updateDistances(distances, theta, k);

        if (hasNegativeCycle(distances))
        {
            return {
                distances,
                theta,
                true
            };
        }
    }

    return {
        distances,
        theta,
        false
    };
}

QVector<QVector<int>> Floyd::initializeDistances(
    const QVector<QVector<int>>& matrix
    )
{
    QVector<QVector<int>> distances =
        matrix;

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (i == j)
            {
                distances[i][j] = 0;
            }

            else if (distances[i][j] == 0)
            {
                distances[i][j] = INT_MAX;
            }
        }
    }

    return distances;
}

QVector<QVector<int>> Floyd::initializeTheta(
    const QVector<QVector<int>>& matrix
    )
{
    int n = matrix.size();

    QVector<QVector<int>> theta(
        n,
        QVector<int>(n, -1)
        );

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] != 0)
            {
                theta[i][j] = i;
            }
        }
    }

    return theta;
}

void Floyd::updateDistances(
    QVector<QVector<int>> &distances,
    QVector<QVector<int>> &theta,
    int k
    )
{
    for (int i = 0; i < distances.size(); ++i)
    {
        if (distances[i][k] != INT_MAX)
        {
            for (int j = 0; j < distances[i].size(); ++j)
            {
                if (distances[k][j] != INT_MAX)
                {
                    int newDistance =
                        distances[i][k] +
                        distances[k][j];

                    if (newDistance < distances[i][j])
                    {
                        distances[i][j] = newDistance;
                        theta[i][j] = theta[k][j];
                    }
                }
            }
        }
    }
}

bool Floyd::hasNegativeCycle(
    const QVector<QVector<int>>& distances)
{
    for (int i = 0; i < distances.size(); ++i)
    {
        if (distances[i][i] < 0)
        {
            return true;
        }
    }

    return false;
}

QVector<int> Floyd::buildPath(
    const QVector<QVector<int>>& theta,
    int start,
    int finish)
{
    QVector<int> path;
    int current = finish;

    while (current != start)
    {
        path.prepend(current);
        current = theta[start][current];

        if (current == -1)
        {
            return {};
        }
    }

    path.prepend(start);
    return path;
}



