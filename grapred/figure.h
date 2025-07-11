#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Figure(QPointF point, QObject *parent = nullptr);
    ~Figure();

    QRectF boundingRect() const override;
    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);
    QPointF startPoint() const;
    QPointF endPoint() const;

    QColor color() const;
    void setColor(const QColor &color);

    void setFill(bool fill);
    bool isFilled() const;

signals:
    void pointChanged();
    void colorChanged();

protected:
    QPointF m_startPoint;
    QPointF m_endPoint;
    QColor m_color;
    bool m_fill = true;

    void updateFigure();
};

#endif // FIGURE_H
