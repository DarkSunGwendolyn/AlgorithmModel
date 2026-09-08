#ifndef DIJKSTRA_H
#define DIJKSTRA_H


#include "graph.h"
#include <QVector>
#include <climits>

struct DijkstraResult
{
    QVector<int> path;
    int pathLen;
};

class Dijkstra
{
public:
    static DijkstraResult findShortestPath(
        const Graph &g,
        int start,
        int finish
        );

    static QVector<QVector<DijkstraResult>> findShortestPaths(
        const Graph &graph
        );

private:
    static int findMinVertex(
        const QVector<int>& dist,
        const QVector<bool>& visited
        );

    static void updateDistances(
        const QVector<QVector<int>>& matrix,
        int current,
        QVector<int>& dist,
        QVector<int>& prev
        );

    static QVector<int> buildPath(
        const QVector<int>& prev,
        int finish
        );

};

#endif // DIJKSTRA_H
