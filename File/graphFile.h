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
        QVector<Vertex>& verticies,
        QVector<QVector<int>>& matrix);

private:

    static void saveVerticies(
        QJsonObject& graphObject,
        const Graph& graph);

    static void saveMatrix(
        QJsonObject& graphObject,
        const Graph& graph);

    static void loadVerticies(
        const QJsonObject &graphObject,
        QVector<Vertex>& verticies
        );

    static void loadMatrix(
        const QJsonObject &graphObject,
        QVector<QVector<int>>& matrix
        );
};

#endif // GRAPHFILE_H
