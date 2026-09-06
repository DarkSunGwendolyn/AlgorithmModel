#ifndef VERTEXITEM_H
#define VERTEXITEM_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneEvent>

class VertexItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit VertexItem(int id, QGraphicsObject *p = nullptr);

    void setId(int id);
    int getId();

    double getRadius() const;

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

    QVariant itemChange(
        GraphicsItemChange change,
        const QVariant &value
    ) override;

private:
    int id;
    bool hovered = false;
    bool highlighted = false;

    static constexpr double RADIUS = 15.0;

signals:
    void positionChanged();
};

#endif // VERTEXITEM_H
