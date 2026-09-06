#include "graph.h"

void Graph::addVertex(double x, double y)
{
    Vertex v;
    v.id = nextVertexID++;
    v.pos = QPointF(x, y);
    verticies.append(v);
}

void Graph::deleteVertex(int id)
{
    verticies.removeAt(id);

    for (int i = id; i < verticies.size(); ++i)
    {
        verticies[i].id--;
    }

    for (int i = 0; i < edges.size(); ++i)
    {
        if (edges[i].from > id)
        {
            edges[i].from--;
        }

        if (edges[i].to > id)
        {
            edges[i].to--;
        }
    }

    nextVertexID = verticies.size();
}

void Graph::addEdge(int from, int to, int weight)
{
    Edge e;
    e.from = from;
    e.to = to;
    e.weight = weight;
    edges.append(e);
}

void Graph::deleteEdge(int from, int to)
{
    for (int i = 0; i < edges.size(); ++i)
    {
        if (edges[i].from == from && edges[i].to == to)
        {
            edges.removeAt(i);
            break;
        }
    }
}

void Graph::changeEdgeWeight(int from, int to, int weight)
{
    for (int i = 0; i < edges.size(); ++i)
    {
        if (edges[i].from == from && edges[i].to == to)
        {
            edges[i].weight = weight;
            break;
        }
    }
}

void Graph::clear()
{
    verticies.clear();
    edges.clear();
    nextVertexID = 0;
}

const QVector<Vertex>& Graph::getVerticies() const
{
    return verticies;
}

const QVector<Edge>& Graph::getEdges() const
{
    return edges;
}

QVector<QVector<int>> Graph::getAdjacencyMatrix() const
{
    QVector<QVector<int>> m(
        verticies.size(), QVector<int>(verticies.size(), 0)
    );

    for (const auto &e : edges)
    {
        int fromIdx = -1;
        int toIdx = -1;

        for (int i = 0; i < verticies.size(); ++i)
        {
            if (verticies[i].id == e.from)
            {
                fromIdx = i;
            }

            if (verticies[i].id == e.to)
            {
                toIdx = i;
            }
        }

        if (fromIdx != -1 && toIdx != -1)
        {
            m[fromIdx][toIdx] = e.weight;
        }
    }

    return m;
}





