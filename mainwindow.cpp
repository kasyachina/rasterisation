#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *v = new QVBoxLayout;
    QHBoxLayout *h1 = new QHBoxLayout;
    QHBoxLayout *h2 = new QHBoxLayout;
    area = new PlotArea();
    log = new LogWidget();
    h1 -> addWidget(area);
    h2 -> addWidget(log);
    v -> addLayout(h1, 75);
    v -> addLayout(h2, 25);
    centralWidget() -> setLayout(v);
    setMinimumSize(500, 600);
    this->setStyleSheet("background-color: white;");
    setWindowTitle("Растеризация");

    log->AppendMessage("abacaba");
    log->AppendMessage("text");
    log->AppendMessage("abracadabra");
    NaiveLine(-1, -1, 5, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
    delete log;
}
//returns transform mask. 1 bit - invert slope, 2 bit - transpose x y
/*int MainWindow::validateLine(int& x1, int& y1, int& x2, int& y2)
{
    int mask = 0;
    if ((y1 - y2) * (x1 - x2) < 0)
    {
        //invert slope
        x1 = -x1;
        x2 = -x2;
        mask |= 1;
    }
    if (std::abs(x1 - x2) > std::abs(y1 - y2))
    {
        //transpose x y
    }
}*/
void MainWindow::NaiveLine(int x1, int y1, int x2, int y2)
{
    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (dx == 0)
    {
        if (y1 > y2)
        {
            std::swap(y1, y2);
        }
        for (int y = y1; y <= y2; ++y)
        {
            area->AddPixel(x1, y);
        }
    }
    else
    {
        for(int x = x1; x <= x2; ++x)
        {
            area->AddPixel(x, y1 + dy * (x - x1) / dx);
        }
    }
}
