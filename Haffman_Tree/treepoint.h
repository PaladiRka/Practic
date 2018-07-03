#ifndef TREEPOINT_H
#define TREEPOINT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <string>


class treePoint : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit treePoint(int x, int y, std::string text, int freq, QObject *parent = 0);
    ~treePoint();
    int x;
    int y;
    int length;
    int freq;
signals:
    void clicked();
public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    std::string text;
};

#endif // TREEPOINT_H
