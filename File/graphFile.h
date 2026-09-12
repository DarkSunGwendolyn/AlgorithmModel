#ifndef GRAPHFILE_H
#define GRAPHFILE_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "graph.h"

class GraphFile
{
public:

    static bool save(
        const QString &fileName,
        const Graph &graph);

    static bool load(
        const QString &fileName,
        QVector<Vertex>& vertices,
        QVector<QVector<int>>& matrix);

private:

    static void saveVertices(
        QJsonObject& graphObject,
        const Graph& graph);

    static void saveMatrix(
        QJsonObject& graphObject,
        const Graph& graph);

    static void loadVertices(
        const QJsonObject &graphObject,
        QVector<Vertex>& vertices
        );

    static void loadMatrix(
        const QJsonObject &graphObject,
        QVector<QVector<int>>& matrix
        );
};

#endif // GRAPHFILE_H
