#ifndef ROMB_H
#define ROMB_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Romb : public Figure
{
    Q_OBJECT

public:
    explicit Romb(QPointF point, QObject *parent = nullptr);
    ~Romb() override = default;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // ROMB_H
