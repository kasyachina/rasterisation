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
    NaiveLine(0, 0, 5, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
    delete log;
}
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
            area->AddPixel(x, y1 + dy * (x - x1) / (qreal)dx);
        }
    }
}
void MainWindow::BresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx = std::abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -std::abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int error = dx + dy;
    while (true)
    {
        area->AddPixel(x1, y1);
        if (x1 == x2 && y1 == y2)
        {
            break;
        }
        int e2 = 2 * error;
        if (e2 >= dy)
        {
            if (x1 == x2)
            {
                break;
            }
            error = error + dy;
            x1 = x1 + sx;
        }
        if (e2 <= dx)
        {
            if (y1 == y2)
            {
                break;
            }
            error = error + dx;
            y1 = y1 + sy;
        }
    }
}
void MainWindow::DDALine(int x1, int y1, int x2, int y2)
{
    qreal dx = (x2 - x1);
    qreal dy = (y2 - y1);
    int step;
    if (abs(dx) >= abs(dy))
      step = abs(dx);
    else
      step = abs(dy);
    dx = dx / step;
    dy = dy / step;
    qreal x = x1;
    qreal y = y1;
    int i = 1;
    while (i <= step) {
      area->AddPixel(x, y);
      x = x + dx;
      y = y + dy;
      i = i + 1;
    }
}
void MainWindow::BresenhamCircle(int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;
    while (x >= y)
    {
        area->AddPixel(x + x0, y + y0);
        area->AddPixel(y + x0, x + y0);
        area->AddPixel(-x + x0, y + y0);
        area->AddPixel(-y + x0, x + y0);
        area->AddPixel(-x + x0, -y + y0);
        area->AddPixel(-y + x0, -x + y0);
        area->AddPixel(x + x0, -y + y0);
        area->AddPixel(y + x0, -x + y0);
        y++;
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}
//void MainWindow::WuLine()
