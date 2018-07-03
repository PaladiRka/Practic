#include "treepoint.h"

treePoint::treePoint(int x, int y, std::string text, int freq, QObject * parent)
    : QObject(parent), QGraphicsItem(), x(x), y(y), text(text), freq(freq)
{
    length=text.size()*6;
    //do something
}

treePoint::~treePoint()
{
    //do anything
}

void treePoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //emit clicked();
    //QGraphicsItem::mousePressEvent(event);
}

void treePoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
    QGraphicsItem::mouseMoveEvent(event);
}

QRectF treePoint::boundingRect() const
{
    return QRectF(x,y,(text.size()*8)+10,15);
}

void treePoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF(x,y,length+10,15));
    painter->setPen(Qt::black);
    painter->setPen(Qt::magenta);
    painter->drawText(QRectF(x+5,y,length*2,15), QString::fromStdString(text));
    painter->drawRect(QRectF(x,y-15,std::to_string(freq).size()*6+1,15));
    painter->drawText(QRectF(x+1,y-15,std::to_string(freq).size()*10,15), QString::fromStdString(std::to_string(freq)));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
