#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "graph.h"
#include "vertexItem.h"
#include "edgeItem.h"
#include "packet.h"
#include "packetItem.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *p = nullptr);

    QVector<QVector<int>> getAdjacencyMatrix() const;

    const Graph& getGraph() const;

    void highlightPath(const QVector<int> &path);

    void setGraphData(
        const QVector<Vertex>& vertices,
        const QVector<QVector<int>>& matrix
        );

    void animatePacket(const Packet &packet);

public slots:

    void setVertexCount(int count);
    void setMatrixValue(int row, int col, int val);

    void deleteVertexById(int id);

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

private:
    QGraphicsScene* scene;
    Graph graph;

    VertexItem *edgeStartVertex = nullptr;
    QGraphicsLineItem *tempLine = nullptr;

    void addVertex(const QPointF& pos);
    void deleteVertex(VertexItem *vItem);
    void deleteVertexEdges(VertexItem *vItem);
    void updateVertexEdges(VertexItem *vItem);
    void changeVerticesIds(int deletedItemId);

    void startEdgeCreation(VertexItem *i);
    void updateEdgeCreation(const QPointF &pos);
    void finishEdgeCreation(VertexItem *vItem);
    void cancelEdgeCreation();
    void deleteEdge(EdgeItem *eItem);
    void changeEdgeWeight(EdgeItem *eItem);

    EdgeItem *findEdge(int from, int to);
    VertexItem * findVertex(int id);

    void createEdge(
        VertexItem *from,
        VertexItem *to,
        int weight);

    void setEdgeWeight(EdgeItem *eItem, int weight);

    void clearHighlight();
    void highlightVertices(const QVector<int> &path);
    void highlightEdges(const QVector<int> &path);

    PacketItem* addPacket(const Packet &packet);

signals:
    void graphChanged();
    void vertexCountChanged(int count);
};


#endif // GRAPHWIDGET_H
