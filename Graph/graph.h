#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "edge.h"

#include <QVector>

class Graph
{
public:
    void addVertex(double x, double y);
    void deleteVertex(int id);

    void addEdge(int from, int to, int weigth);
    void deleteEdge(int from, int to);
    void changeEdgeWeight(int from, int to, int weight);

    void clear();

    const QVector<Vertex>& getVerticies() const;
    const QVector<Edge>& getEdges() const;

    QVector<QVector<int>> getAdjacencyMatrix() const;

private:
    QVector<Vertex> verticies;
    QVector<Edge> edges;

    int nextVertexID = 0;
};


#endif // GRAPH_H
