#include "viewtree.h"
#include "ui_viewtree.h"

viewTree::viewTree(QWidget *parent, Element * root) :
    QWidget(parent),
    ui(new Ui::viewTree)
{
    ui->setupUi(this);
    this->root = root;
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    QPen pet(Qt::blue);
    createTree(root, 0, 0, 0, pet);
    for(int i = 0; i<items.size(); i++)
        scene->addItem(items[i]);
}

void viewTree::createTree(Element * tmp, int x, int y, int parent, QPen pet)
{
    items.push_back(new treePoint(x,y, tmp->expr, tmp->freq));
    int tmp2 = items.size()-1;

    int x_shift = (items.back()->length);

    scene->addLine(items[parent]->x+items[parent]->length/2+5,items[parent]->y+15,items.back()->x+items.back()->length/2+5,items.back()->y, pet);
    QString buf;
    int newX_1 = x+x_shift+15;
    int newX_2 = x-x_shift;
    if(tmp->parent)
    {
        if(tmp->parent->lChild == tmp)
            buf = "0";
        else
            buf = "1";
        scene->addRect((items[parent]->x)+((items.back()->x+items.back()->length/2+5-items[parent]->x+items[parent]->length/2+5)/2)-7, items[parent]->y+40, 10, 8, QPen(Qt::white), QBrush(Qt::white));
        QGraphicsTextItem * tmp3 = scene->addText(buf);
        tmp3->setPos((items[parent]->x)+((items.back()->x+items.back()->length/2+5-items[parent]->x+items[parent]->length/2+5)/2)-7, items[parent]->y+34);

    }
    else
        newX_1*=2;
    if (tmp->rChild)
        createTree(tmp->rChild, newX_1, y+80, tmp2, pet);
    if (tmp->lChild)
        createTree(tmp->lChild, newX_2, y+80, tmp2, pet);

}

viewTree::~viewTree()
{
    delete ui;
}
void viewTree::scaleView(qreal scaleFactor)
{
    qreal factor = ui->graphicsView->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    ui->graphicsView->scale(scaleFactor, scaleFactor);
}

void viewTree::zoomIn()
{
    scaleView(qreal(1.05));
}

void viewTree::zoomOut()
{
    scaleView(1 / qreal(1.05));
}


void viewTree::on_horizontalSlider_sliderMoved(int position)
{
    qreal scpos = position-oldPosSlide;
    oldPosSlide = position;
    if(scpos>0.0)
        zoomIn();
    else
        zoomOut();
}
