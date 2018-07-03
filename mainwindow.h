#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <string>
#include <vector>
#include <algorithm>
#include <QGraphicsWidget>
#include <iostream>
#include <fstream>
#include <QShortcut>

using namespace std;

struct Element
{
    Element(string const & expr, int freq, Element * parent = nullptr, Element * lChild = nullptr, Element * rChild = nullptr) :
        freq(freq), parent(parent), lChild(lChild), rChild(rChild), expr(expr) {}
    Element(Element * v1, Element * v2);
    int freq;
    bool operator <(const Element &v2) { return (this->freq < v2.freq); }
    bool operator==(const Element &v2) { return (this->freq == v2.freq); }
    Element * parent;
    Element * lChild;
    Element * rChild;
    string expr;
};

struct HTElement
{
    HTElement(string path, char symb, int chislo) : binaryView(path), symb(symb), frequency(chislo) {}
    bool operator <(const HTElement &v2) { return (this->symb <  v2.symb); }
    string binaryView;
    char symb;
    int frequency;
};

vector <Element*> & calcFreq(string input);

Element & buildHaffmanTree(vector <Element*> & startFreq);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Element * root = nullptr;
    string output = "";
    string input = "";
    vector<HTElement> table;

private slots:

    void slotShortcutF11();

    void slotShortcutCtrlD();

    void slotShortcutCtrlQ();

    void slotShortcutCtrlS();

    void slotShortcutCtrlO();

    void slotShortcutCtrlEnter();

    void slotShortcutAltEnter();

    void on_pushButton_clicked();

    void on_pushme_clicked();

    void on_pushButton_2_clicked();

    void on_action_3_triggered(bool checked);

    void on_action_triggered(bool checked);

    void on_action_4_triggered(bool checked);

    void on_action_5_triggered(bool checked);

    void on_action_2_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    QShortcut       *keyF11;    // объект горячей клавиши F11
    QShortcut       *keyCtrlD;  // объект сочетания клавиш Ctrl + D
    QShortcut       *keyCtrlQ;  // объект сочетания клавиш Ctrl + Q
    QShortcut       *keyCtrlS;  // объект сочетания клавиш Ctrl + S
    QShortcut       *keyCtrlO;  // объект сочетания клавиш Ctrl + O
    QShortcut       *keyCtrlEnter;  // объект сочетания клавиш Ctrl + Enter
    QShortcut       *keyAltEnter;  // объект сочетания клавиш Alt + Enter
};

#endif // MAINWINDOW_H
