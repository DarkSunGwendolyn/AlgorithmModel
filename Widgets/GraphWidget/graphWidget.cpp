#include "graphWidget.h"

GraphWidget::GraphWidget(QWidget *p) : QGraphicsView(p)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
}

const Graph& GraphWidget::getGraph() const
{
    return graph;
}

void GraphWidget::mousePressEvent(QMouseEvent *e)
{
    QPointF pos = mapToScene(e->position().toPoint());
    QGraphicsItem *item = scene->itemAt(pos, QTransform());
    VertexItem *vItem = dynamic_cast<VertexItem *>(item);
    EdgeItem *eItem = dynamic_cast<EdgeItem *>(item);

    if (e->button() == Qt::LeftButton)
    {

        if (vItem != nullptr && (e->modifiers() & Qt::ControlModifier))
        {
            startEdgeCreation(vItem);
            return;
        }

        if (item == nullptr)
        {
            addVertex(pos);
            return;
        }
    }
    else if(e->button() == Qt::RightButton)
    {
        if (item != nullptr)
        {
            if (vItem != nullptr)
            {
                deleteVertex(vItem);
                return;
            }

            if (eItem != nullptr)
            {
                deleteEdge(eItem);
                return;
            }
        }
    }

    QGraphicsView::mousePressEvent(e);
}

void GraphWidget::setVertexCount(int count)
{
    int currentCount = graph.getVertices().size();

    if (count > currentCount)
    {
        for (int i = currentCount; i < count; ++i)
        {
            QPointF pos(
                100 + (i % 5) * 80,
                100 + (i / 5) * 80
                );

            addVertex(pos);
        }
    }
    else if (count < currentCount)
    {
        for (int i = currentCount - 1; i >= count; --i)
        {
            VertexItem *v = findVertex(i);
            if (v != nullptr)
            {
                deleteVertex(v);
            }
        }
    }
}

void GraphWidget::addVertex(const QPointF& pos)
{
    if (graph.getVertices().size() >= 10)
    {
        QMessageBox::information(
            this,
            "Максимальное количество вершин",
            "Достигнуто максимальное количество вершин"
            );

        return;
    }

    graph.addVertex(pos.x(), pos.y());

    const Vertex& v = graph.getVertices().last();

    VertexItem *item = new VertexItem(v.id);

    item->setPos(pos);

    connect(
        item,
        &VertexItem::positionChanged,
        this,
        [this, item]()
        {
            updateVertexEdges(item);
        }
        );

    scene->addItem(item);

    emit graphChanged();
    emit vertexCountChanged(graph.getVertices().size());
}

void GraphWidget::updateVertexEdges(VertexItem *vItem)
{
    for (QGraphicsItem *item : scene->items())
    {
        EdgeItem *edge = dynamic_cast<EdgeItem *>(item);

        if (edge == nullptr)
            continue;

        if (edge->getFrom() == vItem ||
            edge->getTo() == vItem)
        {
            edge->updatePosition();
        }
    }
}

void GraphWidget::startEdgeCreation(VertexItem *vertex)
{
    edgeStartVertex = vertex;

    tempLine =
        scene->addLine(
            QLineF(
                vertex->pos(),
                vertex->pos()
                ),
            QPen(Qt::black, 2)
            );

    tempLine->setZValue(-1);
}

VertexItem *GraphWidget::findVertex(int id)
{
    for (QGraphicsItem *item : scene->items())
    {
        VertexItem *vertex =
            dynamic_cast<VertexItem *>(item);

        if (vertex != nullptr &&
            vertex->getId() == id)
        {
            return vertex;
        }
    }

    return nullptr;
}

void GraphWidget::deleteVertex(VertexItem *vItem)
{
    if (vItem == nullptr)
    {
        return;
    }

    deleteVertexEdges(vItem);

    int id = vItem->getId();
    graph.deleteVertex(id);
    scene->removeItem(vItem);

    delete vItem;

    changeVerticesIds(id);

    emit graphChanged();
    emit vertexCountChanged(graph.getVertices().size());
}

void GraphWidget::deleteVertexEdges(VertexItem *vItem)
{
    for (QGraphicsItem *i : scene->items())
    {
        EdgeItem *eItem = dynamic_cast<EdgeItem *>(i);

        if (eItem == nullptr)
        {
            continue;
        }

        if (eItem->getFrom() == vItem ||
            eItem->getTo() == vItem)
        {
            graph.deleteEdge(
                eItem->getFrom()->getId(),
                eItem->getTo()->getId()
                );

            scene->removeItem(eItem);
            delete eItem;
        }
    }
}

void GraphWidget::deleteEdge(EdgeItem *eItem)
{
    if (eItem == nullptr)
    {
        return;
    }

    VertexItem* fromVertex = eItem->getFrom();
    VertexItem* toVertex = eItem->getTo();

    graph.deleteEdge(
        fromVertex->getId(),
        toVertex->getId()
        );

    scene->removeItem(eItem);
    delete eItem;

    emit graphChanged();
}

void GraphWidget::changeVerticesIds(int deletetedItemId)
{
    for (QGraphicsItem *item : scene->items())
    {
        VertexItem *vItem = dynamic_cast<VertexItem*>(item);

        if (vItem != nullptr && vItem->getId() > deletetedItemId)
        {
            vItem->setId(vItem->getId()-1);
        }
    }
}

void GraphWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (edgeStartVertex != nullptr)
    {
        QPointF pos =
            mapToScene(e->position().toPoint());

        updateEdgeCreation(pos);
        return;
    }

    QGraphicsView::mouseMoveEvent(e);
}

void GraphWidget::updateEdgeCreation(const QPointF &position)
{
    if (tempLine == nullptr ||
        edgeStartVertex == nullptr)
    {
        return;
    }

    tempLine->setLine(
        QLineF(
            edgeStartVertex->pos(),
            position
            )
        );
}


void GraphWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (edgeStartVertex != nullptr &&
        e->button() == Qt::LeftButton)
    {
        QPointF pos =
            mapToScene(e->position().toPoint());

        QGraphicsItem *item =
            scene->itemAt(pos, QTransform());

        VertexItem *vertex =
            dynamic_cast<VertexItem *>(item);

        if (vertex != nullptr &&
            vertex != edgeStartVertex)
        {
            finishEdgeCreation(vertex);
        }
        else
        {
            cancelEdgeCreation();
        }

        return;
    }

    QGraphicsView::mouseReleaseEvent(e);
}

void GraphWidget::finishEdgeCreation(VertexItem *vItem)
{
    bool ok = false;

    int weight = QInputDialog::getInt(
        this,
        "Вес ребра",
        "Введите вес:",
        1,
        1,
        1000000,
        1,
        &ok
        );

    if (tempLine != nullptr)
    {
        scene->removeItem(tempLine);
        delete tempLine;
        tempLine = nullptr;
    }

    if (ok)
    {
        createEdge(
            edgeStartVertex,
            vItem,
            weight
            );

        emit graphChanged();
    }

    edgeStartVertex = nullptr;
}

void GraphWidget::cancelEdgeCreation()
{
    if (tempLine != nullptr)
    {
        scene->removeItem(tempLine);
        delete tempLine;
        tempLine = nullptr;
    }

    edgeStartVertex = nullptr;
}

void GraphWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton)
    {
        QGraphicsView::mouseDoubleClickEvent(e);
        return;
    }

    QPointF pos =
        mapToScene(e->position().toPoint());

    QGraphicsItem *item =
        scene->itemAt(pos, QTransform());

    EdgeItem *edge =
        dynamic_cast<EdgeItem *>(item);

    if (edge != nullptr)
    {
        changeEdgeWeight(edge);
        return;
    }

    QGraphicsView::mouseDoubleClickEvent(e);
}

void GraphWidget::changeEdgeWeight(EdgeItem *eItem)
{
    if (eItem == nullptr)
    {
        return;
    }

    bool ok = false;

    int weight = QInputDialog::getInt(
        this,
        "Изменение веса",
        "Введите новый вес:",
        eItem->getWeight(),
        1,
        1000000,
        1,
        &ok
        );

    if (!ok)
    {
        return;
    }

    setEdgeWeight(eItem, weight);
    emit graphChanged();
}

void GraphWidget::setEdgeWeight(EdgeItem* eItem, int weight)
{
    if (eItem == nullptr)
    {
        return;
    }

    graph.changeEdgeWeight(
        eItem->getFrom()->getId(),
        eItem->getTo()->getId(),
        weight);

    eItem->setWeight(weight);
}

void GraphWidget::setMatrixValue(int row, int column, int value)
{
    if (value < 0 || row == column)
        return;

    EdgeItem *edge = findEdge(row, column);

    if (value == 0)
    {
        deleteEdge(edge);
        return;
    }

    if (edge != nullptr)
    {
        setEdgeWeight(edge, value);
    }
    else
    {
        createEdge(
            findVertex(row),
            findVertex(column),
            value
            );
    }

    emit graphChanged();
}

void GraphWidget::createEdge(
    VertexItem *from,
    VertexItem *to,
    int weight)
{
    if (from == nullptr || to == nullptr)
    {
        return;
    }

    graph.addEdge(
        from->getId(),
        to->getId(),
        weight
        );

    scene->addItem(
        new EdgeItem(from, to, weight)
        );
}

EdgeItem *GraphWidget::findEdge(int from, int to)
{
    for (QGraphicsItem *item : scene->items())
    {
        EdgeItem *edge =
            dynamic_cast<EdgeItem *>(item);

        if (edge != nullptr &&
            edge->getFrom()->getId() == from &&
            edge->getTo()->getId() == to)
        {
            return edge;
        }
    }

    return nullptr;
}

QVector<QVector<int>>GraphWidget::getAdjacencyMatrix() const
{
    return graph.getAdjacencyMatrix();
}

void GraphWidget::highlightPath(const QVector<int> &path)
{
    clearHighlight();
    highlightVertices(path);
    highlightEdges(path);
}

void GraphWidget::clearHighlight()
{
    for (QGraphicsItem *item : scene->items())
    {
        VertexItem *vItem = dynamic_cast<VertexItem *>(item);

        if (vItem != nullptr &&
            vItem->isHighlighted())
        {
            vItem->setHighlighted(false);
            continue;
        }

        EdgeItem *eItem = dynamic_cast<EdgeItem *>(item);

        if (eItem != nullptr &&
            eItem->isHighlighted())
        {
            eItem->setHighlighted(false);
        }
    }
}

void GraphWidget::highlightVertices(const QVector<int> &path)
{
    for (int id : path)
    {
        VertexItem *vItem = findVertex(id);

        if (vItem != nullptr &&
            !vItem->isHighlighted())
        {
            vItem->setHighlighted(true);
        }
    }
}

void GraphWidget::highlightEdges(const QVector<int> &path)
{
    for (int i = 0; i < path.size() - 1; ++i)
    {
        EdgeItem *eItem = findEdge(path[i], path[i + 1]);

        if (eItem != nullptr &&
            !eItem->isHighlighted())
        {
            eItem->setHighlighted(true);
        }
    }
}

void GraphWidget::setGraphData(
    const QVector<Vertex> &vertices,
    const QVector<QVector<int>>& matrix
    )
{
    edgeStartVertex = nullptr;
    tempLine = nullptr;

    scene->clear();

    graph.setGraphData(vertices, matrix);

    for (const Vertex& vertex : graph.getVertices())
    {
        VertexItem *item = new VertexItem(vertex.id);
        item->setPos(vertex.pos);

        connect(
            item,
            &VertexItem::positionChanged,
            this,
            [this, item]
            {
                updateVertexEdges(item);
            });

        scene->addItem(item);
    }

    for (const Edge& edge : graph.getEdges())
    {
        VertexItem *from = findVertex(edge.from);
        VertexItem *to = findVertex(edge.to);

        if (from != nullptr &&
            to != nullptr)
        {
            scene->addItem(
                new EdgeItem(
                    from,
                    to,
                    edge.weight
                    )
                );
        }
    }

    emit graphChanged();
    emit vertexCountChanged(
        graph.getVertices().size()
        );
}

void GraphWidget::deleteVertexById(int id)
{
    VertexItem *vItem = findVertex(id);

    if (vItem != nullptr)
    {
        deleteVertex(vItem);
    }
}

void GraphWidget::animatePacket(
    const Packet &packet,
    PacketStatus status
    )
{
    PacketItem *pItem = addPacket(packet);

    if (!pItem)
    {
        return;
    }

    QSequentialAnimationGroup *group =
        new QSequentialAnimationGroup(pItem);

    for (int i = 1; i < packet.route.size(); ++i)
    {
        VertexItem *toVertex = findVertex(packet.route[i]);
        QPropertyAnimation *animation =
            new QPropertyAnimation(pItem, "pos");

        animation->setDuration(1000);

        animation->setStartValue(
            findVertex(packet.route[i-1])->pos()
            );
        animation->setEndValue(toVertex->pos());

        group->addAnimation(animation);
    }

    connect(
        group,
        &QSequentialAnimationGroup::finished,
        this,
        [pItem, status](){
            pItem->setStatus(status);

            QTimer::singleShot(
                500,
                pItem,
                &QGraphicsObject::deleteLater
                );
        });

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

PacketItem* GraphWidget::addPacket(const Packet &packet)
{
    VertexItem *vItem = findVertex(packet.currentVertex);

    if (!vItem)
    {
        return nullptr;
    }

    PacketItem *pItem = new PacketItem(packet.id);
    pItem->setPos(vItem->pos());
    scene->addItem(pItem);

    return pItem;
}


