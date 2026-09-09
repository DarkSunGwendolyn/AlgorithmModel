#include "graphFile.h"

bool GraphFile::save(
    const QString &fileName,
    const Graph &graph)
{
    QJsonObject graphObject;
    graphObject["version"] = 1;
    saveVerticies(graphObject, graph);
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

void GraphFile::saveVerticies(
    QJsonObject& graphObject,
    const Graph& graph)
{
    QJsonArray verticiesArray;

    for (const Vertex &vertex : graph.getVerticies())
    {
        QJsonObject vertexObject;

        vertexObject["id"] = vertex.id;
        vertexObject["x"] = vertex.pos.x();
        vertexObject["y"] = vertex.pos.y();

        verticiesArray.append(vertexObject);
    }
    graphObject["verticies"] = verticiesArray;
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
    QVector<Vertex> &verticies,
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

    loadVerticies(
        graphObj,
        verticies
        );

    loadMatrix(
        graphObj,
        matrix
        );

    return true;
}


void GraphFile::loadVerticies(
    const QJsonObject &graphObject,
    QVector<Vertex> &verticies)
{
    QJsonArray verticiesArr =
        graphObject["verticies"].toArray();

    verticies.clear();

    for (const QJsonValue &val : verticiesArr)
    {
        QJsonObject vertexObject = val.toObject();

        Vertex vertex;
        vertex.id = vertexObject["id"].toInt();

        double x = vertexObject["x"].toDouble();
        double y = vertexObject["y"].toDouble();

        vertex.pos = QPointF(x, y);

        verticies.append(vertex);
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
