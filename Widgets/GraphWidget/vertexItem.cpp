#include "vertexItem.h"

VertexItem::VertexItem(int id, QGraphicsObject *p) :
    QGraphicsObject(p), id(id)
{
    setAcceptHoverEvents(true);

    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

int VertexItem::getId()
{
    return id;
}

void VertexItem::setId(int id)
{
    this->id = id;
    update();
}

void VertexItem::setHighlighted(bool highlighted)
{
    this->highlighted = highlighted;
    update();
}

bool VertexItem::isHighlighted()
{
    return highlighted;
}

void VertexItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if (highlighted)
    {
        painter->setBrush(Qt::green);
    }
    else if (isSelected())
    {
        painter->setBrush(Qt::yellow);
    }
    else if (hovered)
    {
        painter->setBrush(Qt::blue);
    }
    else
    {
        painter->setBrush(Qt::white);
    }

    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::black);
    painter->drawText(
        boundingRect(),
        Qt::AlignCenter,
        QString::number(id + 1)
        );
}

QRectF VertexItem::boundingRect() const
{
    return QRectF(
        -RADIUS,
        -RADIUS,
        RADIUS * 2,
        RADIUS * 2
        );
}

void VertexItem::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    hovered = true;
    update();

    QGraphicsItem::hoverEnterEvent(e);
}

void VertexItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    hovered = false;
    update();

    QGraphicsItem::hoverLeaveEvent(e);
}

double VertexItem::getRadius() const
{
    return RADIUS;
}

QVariant VertexItem::itemChange(
    GraphicsItemChange change,
    const QVariant &value)
{
    if (change == ItemPositionHasChanged)
    {
        emit positionChanged();
    }

    return QGraphicsObject::itemChange(change, value);
}

