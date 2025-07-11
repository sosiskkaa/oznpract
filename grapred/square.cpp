#include "square.h"
#include <QPainter>

Square::Square(QPointF point, QObject *parent) :
    Figure(point, parent) {}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect(endPoint().x() > startPoint().x() ? startPoint().x() : endPoint().x(),
                endPoint().y() > startPoint().y() ? startPoint().y() : endPoint().y(),
                qAbs(endPoint().x() - startPoint().x()),
                qAbs(endPoint().y() - startPoint().y()));

    painter->setPen(QPen(color(), 2));
    if (isFilled()) {
        painter->setBrush(QBrush(color()));
    } else {
        painter->setBrush(Qt::NoBrush);
    }
    painter->drawRect(rect);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
