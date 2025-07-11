#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include <QFile>
#include <QTextStream>

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    currentColor = Qt::black;
    m_typeFigure = SquareType;
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

void PaintScene::setFillMode(bool fill) {
    for (auto& figure : figures) {
        figure->setFill(fill);
    }
    update();
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    tempFigure->setEndPoint(event->scenePos());
    this->update(QRectF(0,0,this->width(), this->height()));
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Figure* item = nullptr;

    switch (m_typeFigure) {
    case SquareType:
        item = new Square(event->scenePos());
        break;
    case RombType:
        item = new Romb(event->scenePos());
        break;
    case TriangleType:
        item = new Triangle(event->scenePos());
        break;
    default:
        item = new Square(event->scenePos());
        break;
    }

    item->setPos(event->pos());
    item->setColor(currentColor);
    item->setFill(true);
    tempFigure = item;
    this->addItem(tempFigure);
    figures.emplace_back(tempFigure);
}

void PaintScene::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (const auto& figure : figures) {
        out << figure->metaObject()->className() << ";"
            << figure->startPoint().x() << ";"
            << figure->startPoint().y() << ";"
            << figure->endPoint().x() << ";"
            << figure->endPoint().y() << ";"
            << figure->color().name() << ";"
            << (figure->isFilled() ? "1" : "0") << "\n";
    }
    file.close();
}

void PaintScene::loadFromFile(const QString &fileName)
{
    clear();
    figures.clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(";");

        if (parts.size() != 7) continue;

        QString className = parts[0];
        qreal startX = parts[1].toDouble();
        qreal startY = parts[2].toDouble();
        qreal endX = parts[3].toDouble();
        qreal endY = parts[4].toDouble();
        QColor color(parts[5]);
        bool filled = parts[6] == "1";

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
            figure->setFill(filled);
            addItem(figure);
            figures.emplace_back(figure);
        }
    }
    file.close();
}
