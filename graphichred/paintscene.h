#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include "figure.h"

class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(int typeFigure READ typeFigure WRITE setTypeFigure NOTIFY typeFigureChanged)

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

    enum FigureTypes
    {
        LineType,
        SquareType,
        RombType,
        TriangleType
    };

    int typeFigure() const;
    void setTypeFigure(const int type);
    void setCurrentColor(const QColor &color);
    void setPenSize(int size);
    void setPenOpacity(qreal opacity);
    void setEraser(bool enabled);
    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);

signals:
    void typeFigureChanged();

private:
    Figure *tempFigure;
    int m_typeFigure;
    QColor currentColor;
    QPointF previousPoint;
    int penSize;
    qreal penOpacity;
    bool isEraser;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
