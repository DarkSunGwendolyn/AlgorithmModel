#ifndef PACKETITEM_H
#define PACKETITEM_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneEvent>

#include "packetStatus.h"

class PacketItem : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    explicit PacketItem(int id, QGraphicsObject *p = nullptr);

    void setId(int id);
    int getId();

    void setStatus(PacketStatus status);

protected:
    QRectF boundingRect() const override;

    void paint(
        QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget = nullptr
        ) override;

private:
    PacketStatus status = PacketStatus::Active;

    int id;

    static constexpr double RADIUS = 8.0;

};

#endif // PACKETITEM_H
