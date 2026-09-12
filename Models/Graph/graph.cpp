#include "graph.h"

void Graph::addVertex(double x, double y)
{
    Vertex v;
    v.id = nextVertexID++;
    v.pos = QPointF(x, y);
    vertices.append(v);
}

void Graph::deleteVertex(int id)
{
    vertices.removeAt(id);

    for (int i = id; i < vertices.size(); ++i)
    {
        vertices[i].id--;
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

    nextVertexID = vertices.size();
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
    vertices.clear();
    edges.clear();
    nextVertexID = 0;
}

const QVector<Vertex>& Graph::getVertices() const
{
    return vertices;
}

const QVector<Edge>& Graph::getEdges() const
{
    return edges;
}

QVector<QVector<int>> Graph::getAdjacencyMatrix() const
{
    QVector<QVector<int>> m(
        vertices.size(), QVector<int>(vertices.size(), 0)
    );

    for (const auto &e : edges)
    {
        int fromIdx = -1;
        int toIdx = -1;

        for (int i = 0; i < vertices.size(); ++i)
        {
            if (vertices[i].id == e.from)
            {
                fromIdx = i;
            }

            if (vertices[i].id == e.to)
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

void Graph::setGraphData(
    const QVector<Vertex> &vertices,
    const QVector<QVector<int>> &matrix)
{
    this->vertices = vertices;
    edges.clear();

    for (int i = 0;  i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (matrix[i][j] != 0)
            {
                addEdge(
                    vertices[i].id,
                    vertices[j].id,
                    matrix[i][j]
                    );
            }
        }
    }

    nextVertexID = vertices.size();
}





