#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QColor>

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(QPointF startPoint READ startPoint WRITE setStartPoint NOTIFY pointChanged)
    Q_PROPERTY(QPointF endPoint READ endPoint WRITE setEndPoint NOTIFY pointChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit Figure(QPointF point, QObject *parent = 0);
    virtual ~Figure() override;

    QPointF startPoint() const;
    QPointF endPoint() const;
    QColor color() const;

    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);
    void setColor(const QColor &color);

    QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

signals:
    void pointChanged();
    void colorChanged();

private:
    QPointF m_startPoint;
    QPointF m_endPoint;
    QColor m_color;

public slots:
    void updateFigure();
};

#endif // FIGURE_H
