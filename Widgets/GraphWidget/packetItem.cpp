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

void PacketItem::setStatus(PacketStatus status)
{
    this->status = status;
    update();
}

void PacketItem::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if (status == PacketStatus::Active)
    {
        painter->setBrush(Qt::black);
        painter->setPen(Qt::black);
    }
    else if(status == PacketStatus::Delivered)
    {
        painter->setBrush(Qt::green);
        painter->setPen(Qt::green);
    }
    else
    {
        painter->setBrush(Qt::red);
        painter->setPen(Qt::red);
    }

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
