#ifndef EDGEITEM_H
#define EDGEITEM_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <cmath>

#include "vertexItem.h"

class EdgeItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit EdgeItem(VertexItem *from,
                      VertexItem *to,
                      int weight,
                      QGraphicsObject *p = nullptr);

    VertexItem *getFrom() const;
    VertexItem *getTo() const;

    void setWeight(int weight);
    int getWeight() const;

    void updatePosition();

    void setHighlighted(bool highlighted);
    bool isHighlighted();

protected:
    QRectF boundingRect() const override;

    void paint(
        QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget = nullptr
        ) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *e) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *e) override;

private:
    VertexItem *from;
    VertexItem *to;
    int weight;

    bool hovered = false;
    bool highlighted = false;

    static constexpr double ARROW_SIZE = 10.0;

    QLineF getLine() const;

    void drawLine(
        QPainter *painter,
        const QLineF &line
        ) const;

    void drawArrow(
        QPainter *painter,
        const QLineF &line
        ) const;

    void drawWeight(
        QPainter *painter,
        const QLineF &line
        ) const;

};

#endif // EDGEITEM_H
