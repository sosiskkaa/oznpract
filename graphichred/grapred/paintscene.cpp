#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include <QFile>
#include <QTextStream>

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    currentColor = Qt::black;
}

PaintScene::~PaintScene() {}

int PaintScene::typeFigure() const {
    return m_typeFigure;
}

void PaintScene::setTypeFigure(const int type) {
    m_typeFigure = type;
}

void PaintScene::setCurrentColor(const QColor &color) {
    currentColor = color;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    tempFigure->setEndPoint(event->scenePos());
    this->update(QRectF(0,0,this->width(), this->height()));
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (m_typeFigure) {
    case SquareType: {
        Square *item = new Square(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    case RombType: {
        Romb *item = new Romb(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    case TriangleType: {
        Triangle *item = new Triangle(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    default: {
        Square *item = new Square(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    }

    tempFigure->setColor(currentColor);
    this->addItem(tempFigure);
}

void PaintScene::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    foreach(QGraphicsItem *item, items()) {
        if (Figure *figure = dynamic_cast<Figure*>(item)) {
            out << figure->metaObject()->className() << ";"
                << figure->startPoint().x() << ";"
                << figure->startPoint().y() << ";"
                << figure->endPoint().x() << ";"
                << figure->endPoint().y() << ";"
                << figure->color().name() << "\n";
        }
    }
    file.close();
}

void PaintScene::loadFromFile(const QString &fileName)
{
    clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(";");

        if (parts.size() != 6) continue;

        QString className = parts[0];
        qreal startX = parts[1].toDouble();
        qreal startY = parts[2].toDouble();
        qreal endX = parts[3].toDouble();
        qreal endY = parts[4].toDouble();
        QColor color(parts[5]);

        Figure *figure = nullptr;
        QPointF startPoint(startX, startY);

        if (className == "Romb") {
            figure = new Romb(startPoint);
        } else if (className == "Square") {
            figure = new Square(startPoint);
        } else if (className == "Triangle") {
            figure = new Triangle(startPoint);
        }

        if (figure) {
            figure->setEndPoint(QPointF(endX, endY));
            figure->setColor(color);
            addItem(figure);
        }
    }
    file.close();
}
