#include "graphFile.h"

bool GraphFile::save(
    const QString &fileName,
    const Graph &graph)
{
    QJsonObject graphObject;
    graphObject["version"] = 1;
    saveVertices(graphObject, graph);
    saveMatrix(graphObject, graph);

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QJsonDocument document(graphObject);
    file.write(
        document.toJson(QJsonDocument::Indented)
        );

    file.close();
    return true;
}

void GraphFile::saveVertices(
    QJsonObject& graphObject,
    const Graph& graph)
{
    QJsonArray verticesArray;

    for (const Vertex &vertex : graph.getVertices())
    {
        QJsonObject vertexObject;

        vertexObject["id"] = vertex.id;
        vertexObject["x"] = vertex.pos.x();
        vertexObject["y"] = vertex.pos.y();

        verticesArray.append(vertexObject);
    }
    graphObject["vertices"] = verticesArray;
}

void GraphFile::saveMatrix(
    QJsonObject& graphObject,
    const Graph& graph)
{
    QJsonArray matrixArray;
    QVector<QVector<int>> matrix = graph.getAdjacencyMatrix();

    for (const QVector<int> &row : matrix)
    {
        QJsonArray rowArray;

        for (int val : row)
        {
            rowArray.append(val);
        }

        matrixArray.append(rowArray);
    }

    graphObject["matrix"] = matrixArray;
}

bool GraphFile::load(
    const QString &fileName,
    QVector<Vertex> &vertices,
    QVector<QVector<int>>& matrix
    )
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    if (doc.isNull() ||
        !doc.isObject())
    {
        return false;
    }

    QJsonObject graphObj = doc.object();

    loadVertices(
        graphObj,
        vertices
        );

    loadMatrix(
        graphObj,
        matrix
        );

    return true;
}


void GraphFile::loadVertices(
    const QJsonObject &graphObject,
    QVector<Vertex> &vertices)
{
    QJsonArray verticesArr =
        graphObject["vertices"].toArray();

    vertices.clear();

    for (const QJsonValue &val : verticesArr)
    {
        QJsonObject vertexObject = val.toObject();

        Vertex vertex;
        vertex.id = vertexObject["id"].toInt();

        double x = vertexObject["x"].toDouble();
        double y = vertexObject["y"].toDouble();

        vertex.pos = QPointF(x, y);

        vertices.append(vertex);
    }
}

void GraphFile::loadMatrix(
    const QJsonObject &graphObject,
    QVector<QVector<int>>& matrix)
{
    QJsonArray matrixArr =
        graphObject["matrix"].toArray();

    matrix.clear();

    for (const QJsonValue &rowVal : matrixArr)
    {
        QJsonArray rowObject = rowVal.toArray();
        QVector<int> row;

        for (const QJsonValue &val : rowObject)
        {
            row.append(val.toInt());
        }

        matrix.append(row);
    }
}
