#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <vector>
#include <memory>

#include "figure.h"

class PaintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PaintScene(QObject *parent = nullptr);
    ~PaintScene();

    enum FigureTypes {
        SquareType,
        RombType,
        TriangleType
    };

    int typeFigure() const;
    void setTypeFigure(const int type);
    void setCurrentColor(const QColor &color);
    void setFillMode(bool fill);

    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);

private:
    Figure* tempFigure;
    int m_typeFigure;
    QColor currentColor;
    std::vector<std::unique_ptr<Figure>> figures;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PAINTSCENE_H
