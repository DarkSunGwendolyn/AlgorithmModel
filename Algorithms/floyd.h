#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"
#include <QVector>
#include <climits>

struct FloydMatrixResult
{
    QVector<QVector<int>> distances;
    QVector<QVector<int>> theta;
    bool negativeCycle;
};

struct FloydResult
{
    QVector<int> path;
    int pathLen;
    bool negativeCycle;
};

class Floyd
{
public:
    static FloydMatrixResult findShortestPaths(
        const Graph &graph
        );

    static FloydResult findShortestPath(
        const Graph &graph,
        int start,
        int finish
        );

    static QVector<int> getPath(
        const FloydMatrixResult &result,
        int start,
        int finish);

private:

    static QVector<QVector<int>>  initializeDistances(
        const QVector<QVector<int>>& matrix
        );

    static QVector<QVector<int>> initializeTheta(
        const QVector<QVector<int>>& matrix
        );

    static void updateDistances(
        QVector<QVector<int>> &distances,
        QVector<QVector<int>> &theta,
        int k
        );

    static bool hasNegativeCycle(
        const QVector<QVector<int>>& distances
        );

    static QVector<int> buildPath(
        const QVector<QVector<int>>& theta,
        int start,
        int finish
        );
};

#endif // FLOYD_H
