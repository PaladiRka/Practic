#include "mainwindow.h"
#include "viewtree.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(this->style()->standardIcon(QStyle::SP_TrashIcon));
    this->move(this->pos()-QPoint(-300, 0));
    this->setWindowTitle("Haffman algo coder");
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("Символ")
                                                             << trUtf8("Количество")
                                                             << trUtf8("Кодировка")
                                               );
    keyF11 = new QShortcut(this);   // Инициализируем объект
    keyF11->setKey(Qt::Key_F11);    // Устанавливаем код клавиши
    // цепляем обработчик нажатия клавиши
    connect(keyF11, SIGNAL(activated()), this, SLOT(slotShortcutF11()));

    keyCtrlD = new QShortcut(this); // Инициализируем объект
    keyCtrlD->setKey(Qt::CTRL + Qt::Key_D); // Устанавливаем сочетание клавиш
    // подключаем обработчик нажатия клавиши
    connect(keyCtrlD, SIGNAL(activated()), this, SLOT(slotShortcutCtrlD()));

    keyCtrlQ = new QShortcut(this); // Инициализируем объект
    keyCtrlQ->setKey(Qt::CTRL + Qt::Key_Q); // Устанавливаем сочетание клавиш
    // подключаем обработчик нажатия клавиши
    connect(keyCtrlQ, SIGNAL(activated()), this, SLOT(slotShortcutCtrlQ()));

    keyCtrlS = new QShortcut(this); // Инициализируем объект
    keyCtrlS->setKey(Qt::CTRL + Qt::Key_S); // Устанавливаем сочетание клавиш
    // подключаем обработчик нажатия клавиши
    connect(keyCtrlS, SIGNAL(activated()), this, SLOT(slotShortcutCtrlS()));

    keyCtrlO = new QShortcut(this); // Инициализируем объект
    keyCtrlO->setKey(Qt::CTRL + Qt::Key_O); // Устанавливаем сочетание клавиш
    // подключаем обработчик нажатия клавиши
    connect(keyCtrlO, SIGNAL(activated()), this, SLOT(slotShortcutCtrlO()));

    keyCtrlEnter = new QShortcut(this); // Инициализируем объект
    keyCtrlEnter->setKey(Qt::CTRL + Qt::Key_Enter); // Устанавливаем сочетание клавиш
    // подключаем обработчик нажатия клавиши
    connect(keyCtrlEnter, SIGNAL(activated()), this, SLOT(slotShortcutCtrlEnter()));

    keyAltEnter = new QShortcut(this); // Инициализируем объект
    keyAltEnter->setKey(Qt::ALT + Qt::Key_Enter); // Устанавливаем сочетание клавиш
    // подключаем обработчик нажатия клавиши
    connect(keyAltEnter, SIGNAL(activated()), this, SLOT(slotShortcutAltEnter()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotShortcutF11()
{
    /* В этом обработчике сделаем переключение приложения
     * в полноэкранный режим и обратно в нормальный режим окна
     * */
    if(this->isFullScreen()){
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}

void MainWindow::slotShortcutCtrlD()
{
    /* Для обработки сочетания клавив Ctrl + D
     * Информационный MessageBox
     * */
    QMessageBox::information(this,
                             "Горячая клавиша",
                             "Мои поздравления!!! Горячая клавиша работает",
                             QMessageBox::Ok);
}

void MainWindow::slotShortcutCtrlQ()
{
    /* Для обработки сочетания клавив Ctrl + Q
     * Вызов события "Выход"
     * */
    on_action_3_triggered(true);
}

void MainWindow::slotShortcutCtrlS()
{
    /* Для обработки сочетания клавив Ctrl + S
     * Вызов события "Сохранение"
     * */
    on_action_4_triggered(true);
}

void MainWindow::slotShortcutCtrlO()
{
    /* Для обработки сочетания клавив Ctrl + O
     * Вызов события "Открыть файл..."
     * */
    on_action_triggered(true);
}

void MainWindow::slotShortcutCtrlEnter()
{
    /* Для обработки сочетания клавив Ctrl + Enter
     * Вызов события при нажимании на кнопку "ЗАКОДИРОВАТЬ"
     * */
    on_pushButton_clicked();
}

void MainWindow::slotShortcutAltEnter()
{
    /* Для обработки сочетания клавив Alt + Enter
     * Вызов события при нажимании на кнопку "ДЕКОДИРОВАТЬ"
     * */
    on_pushme_clicked();
}

vector<Element*> & calcFreq(string input)
{
    vector <Element*> & startVals = *(new vector <Element*>);
    int tmp;
    for (int i = 0; i < input.size(); i++)
    {
        tmp = 1;
        int counter = 0;
        char find = input[i];
        if (!find)
            continue;
        while (tmp>=0)
        {
            tmp = input.find(find);
            if (tmp>=0)
            {
                input[tmp] = '\0';
                counter++;
            }
        }
        string tmp;
        if(find == '\n')
            tmp = "'\\n'";
        else if(find == ' ' )
            tmp = "'_'";
        else
            tmp.insert(tmp.begin(), find);
        Element * buf = new Element(tmp, counter);
        startVals.push_back(buf);
    }
    return startVals;
}

Element & buildHaffmanTree(vector<Element*>& startFreq)
{
    if (startFreq.size() == 1)
        return *startFreq[0];

    int lessEl_1 = 0;
    int lessEl_2 = 1;
    if (*startFreq[lessEl_2] < *startFreq[lessEl_1])
    {
        Element * buf = startFreq[lessEl_1];
        startFreq[lessEl_1] = startFreq[lessEl_2];
        startFreq[lessEl_2] = buf;
    }
    for (int i = 1; i < startFreq.size(); i++)
    {
        if ((*startFreq[i] < *startFreq[lessEl_2]))
        {
            if (*startFreq[i] < *startFreq[lessEl_1])
            {
                lessEl_2 = lessEl_1;
                lessEl_1 = i;
            }
            else
                lessEl_2 = i;
        }
    }
    Element * tmp = new Element(startFreq[lessEl_1], startFreq[lessEl_2]);
    startFreq[lessEl_1] = tmp;
    startFreq.erase(startFreq.begin()+lessEl_2);
    buildHaffmanTree(startFreq);
}

void calcHaffmanTable(Element * rootHaffmanTree, vector <HTElement> & table, string path)
{
    if (rootHaffmanTree->lChild)
        calcHaffmanTable(rootHaffmanTree->lChild, table, path+'0');
    if (rootHaffmanTree->rChild)
        calcHaffmanTable(rootHaffmanTree->rChild, table, path+'1');
    if (!rootHaffmanTree->rChild && !rootHaffmanTree->lChild)
    {
        if(table.size()==0 && path.size() == 0)
            path = "1";
        if(rootHaffmanTree->expr == "'\\n'")
            table.push_back(HTElement(path, '\n', rootHaffmanTree->freq));
        else if(rootHaffmanTree->expr == "'_'")
            table.push_back(HTElement(path, ' ', rootHaffmanTree->freq));
        else
            table.push_back(HTElement(path, rootHaffmanTree->expr[0], rootHaffmanTree->freq));
    }
}

Element::Element(Element *v1, Element *v2)
{
    expr = v1->expr + v2->expr;
    freq = v1->freq + v2->freq;
    lChild = v1;
    rChild = v2;
    parent = nullptr;
    v1->parent = this;
    v2->parent = this;
}

struct sort_class_x
{
    bool operator() (Element * v1, Element * v2)
    { return (v1->expr[0] < v2->expr[0]);}
} sort_alph;

void MainWindow::on_pushButton_clicked()
{
    if(input == ui->textEdit->toPlainText().toStdString())
    {
        ui->textBrowser->setText(QString::fromStdString(output));
        return;
    }
    else
        input = ui->textEdit->toPlainText().toStdString();
    if(!input.size())
    {
        QMessageBox msgBox;
        msgBox.setText("Информация:");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setInformativeText("Введенное вами сообщение пусто, его кодировка невозможна, попробуйте снова.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.move(this->pos()+QPoint(104, 304));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    vector<Element*> & startVals = calcFreq(input);
    ui->tableWidget->setRowCount(startVals.size());
    ui->tableWidget->setColumnCount(3);
    sort(startVals.begin(), startVals.end(), sort_alph);
    for (int i = 0; i < startVals.size(); i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(startVals[i]->expr.c_str()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem((to_string(startVals[i]->freq)).c_str()));
    }
    root = &buildHaffmanTree(startVals);
    table.clear();
    calcHaffmanTable(root, table, "");
    sort(table.begin(), table.end());

    for (int i = 0; i < table.size(); i++)
    {
        string buf3 = "";
        switch (table[i].symb) {
        case '  ':
            buf3 = "->";
            break;
        case ' ':
            buf3 = "space";
            break;
        case '\n':
            buf3 = "\\n";
            break;
        default:
            buf3 += table[i].symb;
            break;
        }
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(table[i].binaryView.c_str()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem((to_string(table[i].frequency)).c_str()));
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(buf3)));
    }
    delete &startVals;
    output = "";
    ui->label->setText("Закодированное сообщение:");
    for(int i = 0; i<input.size(); i++)
        for(int k = 0; k<table.size(); k++)
            if(input[i]==table[k].symb)
            {
                output+=table[k].binaryView;
                break;
            }
    int def_size = input.size()*sizeof(char)*8;
    int encoded_size = output.size();
    int profit = def_size-encoded_size;
    ui->textBrowser->setText(QString::fromStdString(output));
    QMessageBox msgBox;
    msgBox.setText("Успех!");
    msgBox.setIcon(QMessageBox::Information);
    QString nya = "Исходный размер сообщения " + QString::fromStdString(std::to_string(def_size)) + " бит.\n" + "Размер закодированного сообщения: " + QString::fromStdString(std::to_string(encoded_size)) + " бит.\n" + "Cообщение сжато на " + QString::fromStdString(std::to_string(profit)) + " бит.";
    msgBox.setInformativeText(nya);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.move(this->pos()+QPoint(104, 304));
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    return;
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!root)
    {
        QMessageBox msgBox;
        msgBox.setText("!ВНИМАНИЕ!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setInformativeText("Дерево не может быть отображено, так как ничего не было закодировано.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.move(this->pos()+QPoint(104, 304));
        msgBox.exec();
        return;
    }
    viewTree *tree = new viewTree(nullptr, root);
    tree->move(this->pos()+QPoint(417,0));
    tree->setWindowTitle("HAFFMAN TREE VIEW");
    tree->setWindowIcon(this->style()->standardIcon(QStyle::SP_CommandLink));
    tree->show();
}

void MainWindow::on_pushme_clicked()
{
    if(!output.size())
    {
        QMessageBox msgBox;
        msgBox.setText("!ВНИМАНИЕ!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setInformativeText("Нет данных для декодирования, попробуйте сначала что-нибудь закодировать!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.move(this->pos()+QPoint(104, 304));
        msgBox.exec();
        return;
    }
    string tmp = "";
    for(int i = 0; i<output.size(); i++)
    {
        for(int k = 0; k<table.size(); k++)
        {
            bool passed = 1;
            for(int j = 0; j<table[k].binaryView.size(); j++, i++)
            {

                if(output[i] != table[k].binaryView[j])
                {
                    i-=j;
                    passed = 0;
                    break;
                }
            }
            if(passed)
            {
                tmp += table[k].symb;
                i--;
                break;
            }
        }
    }
    ui->textBrowser->setText(QString::fromStdString(tmp));
    ui->label->setText("Декодированное сообщение:");
}

void MainWindow::on_action_3_triggered(bool checked)
{
    exit(0);
}

void MainWindow::on_action_triggered(bool checked)
{
    QString gphFile = QFileDialog::getOpenFileName(this, tr("Open file"),
                      QCoreApplication::applicationDirPath(), tr(""));
    std::ifstream finput(gphFile.toStdString());
    gphFile = "";
    char buf = finput.get();
    while(buf != EOF)
    {
        gphFile.append(QChar(buf));
        buf = finput.get();
    }

    if(gphFile.isEmpty())
        return;

    ui->textEdit->setText(gphFile);
    finput.close();
}

void MainWindow::on_action_4_triggered(bool checked)
{
    QString gphFile = QFileDialog::getSaveFileName(this, tr("Save Massage"), QCoreApplication::applicationDirPath(), tr("Text (*.txt)"));
    std::ofstream fout(gphFile.toStdString());

    gphFile = QString::fromStdString(output);

    fout << gphFile.toStdString() << std::endl << std::endl;
    for(int i = 0; i < table.size(); i++)
    {
        QString check = "";
        QTableWidgetItem *item0 = ui->tableWidget->item(i,0);
        QTableWidgetItem *item2 = ui->tableWidget->item(i,2);
        if (NULL != item0)
        {
           check += item0->text();
        }
        else
        {
            check += ' ';
        }
        check += '    ';
        if (NULL != item2)
        {
           check += item2->text();
        }
        string out = check.toStdString();
        fout << out << std::endl;
    }

    fout.close();
}

void MainWindow::on_action_5_triggered(bool checked)
{
    QMessageBox::information(this,
                             "Информация:",
                             "Прогрмма созданна на Qt 5.11",
                             QMessageBox::Ok);
}

void MainWindow::on_action_2_triggered(bool checked)
{
    QMessageBox::information(this,
                             "Горячие клавиши",
                             "F11 - полноэкранный режим\nCtrl + Q - выход\nCtrl + S - Сохранить\nCtrl + O - Открыть\nCtrl + Enter - Закодировать\nAlt + Enter - Декодировать",
                             QMessageBox::Ok);
}
