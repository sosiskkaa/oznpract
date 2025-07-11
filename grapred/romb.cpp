#include "romb.h"
#include <QPainter>

Romb::Romb(QPointF point, QObject *parent) :
    Figure(point, parent) {}

void Romb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygonF polygon;
    polygon << QPointF(startPoint().x() + (endPoint().x() > startPoint().x() ? +1 : -1)*
                                              abs((endPoint().x() - startPoint().x())/2), startPoint().y())
            << QPointF(endPoint().x(), startPoint().y() + (endPoint().y() > startPoint().y() ? +1 : -1)*
                                                              abs((endPoint().y() - startPoint().y())/2))
            << QPointF(startPoint().x() + (endPoint().x() > startPoint().x() ? +1 : -1)*
                                              abs((endPoint().x() - startPoint().x())/2), endPoint().y())
            << QPointF(startPoint().x(), startPoint().y() + (endPoint().y() > startPoint().y() ? +1 : -1)*
                                                                abs((endPoint().y() - startPoint().y())/2));

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
