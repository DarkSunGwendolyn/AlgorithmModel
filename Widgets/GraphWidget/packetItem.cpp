#include "packetItem.h"

PacketItem::PacketItem(int id, QGraphicsObject *p) :
    QGraphicsObject(p), id(id)
{

}

void PacketItem::setId(int id)
{
    this->id = id;
}

int PacketItem::getId()
{
    return id;
}

void PacketItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawEllipse(boundingRect());
    painter->setPen(Qt::white);
    painter->drawText(
        boundingRect(),
        Qt::AlignCenter,
        QString::number(id + 1)
        );
}

QRectF PacketItem::boundingRect() const
{
    return QRectF(
        -RADIUS,
        -RADIUS,
        RADIUS * 2,
        RADIUS * 2
        );
}
