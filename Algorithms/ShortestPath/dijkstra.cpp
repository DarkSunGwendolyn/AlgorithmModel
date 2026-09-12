#include "dijkstra.h"

QVector<QVector<DijkstraResult>> Dijkstra::findShortestPaths(
    const Graph &graph)
{
    int n = graph.getAdjacencyMatrix().size();
    QVector<QVector<DijkstraResult>> results (
        n,
        QVector<DijkstraResult>(n)
        );

    for (int from = 0; from < n; ++from)
    {
        for (int to = 0; to < n; ++to)
        {
            results[from][to] =
                findShortestPath(graph,from,to);
        }
    }

    return results;
}

DijkstraResult Dijkstra::findShortestPath(
    const Graph& graph,
    int start,
    int finish
    )
{
    QVector<QVector<int>> matrix =
        graph.getAdjacencyMatrix();

    int n = matrix.size();

    QVector<int> distance(n, INT_MAX);
    QVector<bool> visited(n, false);
    QVector<int> prev(n, -1);

    distance[start] = 0;

    for (int i = 0; i < n; ++i)
    {

        int current = findMinVertex(distance, visited);

        if (current == -1 ||
            distance[current] == INT_MAX)
        {
            break;
        }

        visited[current] = true;

        updateDistances(
            matrix,
            current,
            distance,
            prev
            );

        if (current == finish)
        {
            break;
        }
    }

    if (distance[finish] == INT_MAX)
    {
        return {{}, INT_MAX};
    }

    return {
        buildPath(prev, finish),
        distance[finish]
    };
}


int Dijkstra::findMinVertex(
    const QVector<int>& dist,
    const QVector<bool>& visited
    )
{
    int current = -1;

    for (int j = 0; j < dist.size(); ++j)
    {
        if (!visited[j] &&
            (current == -1 ||
             dist[j] < dist[current]))
        {
            current = j;
        }
    }

    return current;
}


void Dijkstra::updateDistances(
    const QVector<QVector<int>>& matrix,
    int current,
    QVector<int>& dist,
    QVector<int>& prev
    )
{
    for (int j = 0; j < dist.size(); ++j)
    {
        if (matrix[current][j] != 0)
        {
            int newDistance = dist[current] + matrix[current][j];

            if (newDistance < dist[j])
            {
                dist[j] = newDistance;
                prev[j] = current;
            }
        }
    }
}

QVector<int> Dijkstra::buildPath(
    const QVector<int>& prev,
    int finish
    )
{
    QVector<int> path;
    int current = finish;

    while(current != -1)
    {
        path.prepend(current);
        current = prev[current];
    }

    return path;
}
