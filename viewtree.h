#ifndef VIEWTREE_H
#define VIEWTREE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <vector>
#include "mainwindow.h"
#include "treepoint.h"

namespace Ui {
class viewTree;
}

class viewTree : public QWidget
{
    Q_OBJECT

public slots:
    void zoomIn();
    void zoomOut();
public:
    Element * root;
    explicit viewTree(QWidget *parent = 0, Element * troot = 0);
    void createTree(Element * tmp, int x, int y, int parent, QPen pet);
    ~viewTree();
    QGraphicsScene * scene;
    treePoint       *point;
    std::vector <treePoint*> items;
    int oldPosSlide = 50;
protected:
    void scaleView(qreal scaleFactor);

private slots:
    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::viewTree *ui;
};

#endif // VIEWTREE_H
