#include "edgeItem.h"

EdgeItem::EdgeItem(VertexItem *from,
                   VertexItem *to,
                   int weight,
                   QGraphicsObject *p) :
    QGraphicsObject(p), weight(weight),from(from), to(to)
{
    setZValue(-1);

    setAcceptHoverEvents(true);

    setAcceptedMouseButtons(Qt::NoButton);
}

void EdgeItem::setHighlighted(bool highlighted)
{
    this->highlighted = highlighted;

    if (highlighted)
    {
        setZValue(-0.5);
    }
    else
    {
        setZValue(-1);
    }

    update();
}

bool EdgeItem::isHighlighted()
{
    return highlighted;
}

QRectF EdgeItem::boundingRect() const
{
    return QRectF(
        from->pos(),
        to->pos()
    ).normalized().adjusted(
        -ARROW_SIZE,
        -ARROW_SIZE,
        ARROW_SIZE,
        ARROW_SIZE
    );
}

void EdgeItem::paint(
    QPainter *painter,
    const QStyleOptionGraphicsItem *,
    QWidget *)
{
    QLineF line = getLine();

    if (line.length() <= 0)
        return;

    painter->setRenderHint(QPainter::Antialiasing);

    drawLine(painter, line);
    drawArrow(painter, line);
    drawWeight(painter, line);
}

QLineF EdgeItem::getLine() const
{
    QLineF centerLine(from->pos(), to->pos());

    if (centerLine.length() == 0)
        return QLineF();

    QPointF direction = centerLine.p2() - centerLine.p1();

    double length = std::sqrt(
        direction.x() * direction.x() +
        direction.y() * direction.y()
        );

    direction /= length;

    QPointF start = centerLine.p1()
                    + direction * from->getRadius();

    QPointF end = centerLine.p2()
                  - direction * to->getRadius();

    return QLineF(start, end);
}

void EdgeItem::drawLine(
    QPainter *painter,
    const QLineF &line
    ) const
{
    if (highlighted)
    {
        painter->setPen(QPen(Qt::green, 2));
    }
    else if (hovered)
    {
        painter->setPen(QPen(Qt::blue, 2));
    }
    else
    {
        painter->setPen(QPen(Qt::black, 2));
    }

    painter->setBrush(Qt::NoBrush);
    painter->drawLine(line);
}

void EdgeItem::drawArrow(
    QPainter *painter,
    const QLineF &line
    ) const
{
    double angle = std::atan2(
        -line.dy(),
        line.dx()
        );

    QPointF arrowP1 = line.p2() - QPointF(
                          std::cos(angle + M_PI / 6) * ARROW_SIZE,
                          -std::sin(angle + M_PI / 6) * ARROW_SIZE
                          );

    QPointF arrowP2 = line.p2() - QPointF(
                          std::cos(angle - M_PI / 6) * ARROW_SIZE,
                          -std::sin(angle - M_PI / 6) * ARROW_SIZE
                          );

    QPolygonF arrowHead;

    arrowHead << line.p2()
              << arrowP1
              << arrowP2;

    if (highlighted)
    {
        painter->setBrush(Qt::green);
    }
    else if (hovered)
    {
        painter->setBrush(Qt::blue);
    }
    else
    {
        painter->setBrush(Qt::black);
    }
    painter->drawPolygon(arrowHead);
}

void EdgeItem::drawWeight(
    QPainter *painter,
    const QLineF &line
    ) const
{
    QPointF center = line.center();

    if (highlighted)
    {
        painter->setPen(Qt::green);
    }
    else if (hovered)
    {
        painter->setPen(Qt::blue);
    }
    else
    {
         painter->setPen(Qt::black);
    }

    painter->setBrush(Qt::white);
    center.setY(center.y() - 10);

    QRectF rect(
        center.x() - 15,
        center.y() - 12,
        30,
        24
        );

    //painter->drawRect(rect);

    painter->drawText(
        rect,
        Qt::AlignCenter,
        QString::number(weight)
        );
}

VertexItem *EdgeItem::getFrom() const
{
    return from;
}

VertexItem *EdgeItem::getTo() const
{
    return to;
}

void EdgeItem::setWeight(int weight)
{
    this->weight = weight;
    update();
}

int EdgeItem::getWeight() const
{
    return weight;
}

void EdgeItem::updatePosition()
{
    prepareGeometryChange();
    update();
}
void EdgeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    hovered = true;
    update();

    QGraphicsItem::hoverEnterEvent(e);
}

void EdgeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    hovered = false;
    update();

    QGraphicsItem::hoverLeaveEvent(e);
}




