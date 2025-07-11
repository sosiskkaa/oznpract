#include "triangle.h"
#include <QPainter>

Triangle::Triangle(QPointF point, QObject *parent) :
    Figure(point, parent) {}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygonF polygon;
    polygon << QPointF((startPoint().x() + endPoint().x()) / 2, startPoint().y())
            << QPointF(endPoint().x(), endPoint().y())
            << QPointF(startPoint().x(), endPoint().y());

    painter->setPen(QPen(color(), 2));
    if (isFilled()) {
        painter->setBrush(QBrush(color()));
    } else {
        painter->setBrush(Qt::NoBrush);
    }
    painter->drawPolygon(polygon);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
