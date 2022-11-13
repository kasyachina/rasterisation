#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    area = new PlotArea();
    log = new LogWidget();
    setStyleSheet("background-color: white;");

    QGridLayout *g = new QGridLayout;

    g -> addWidget(area, 0, 0, 12, 4);
    g -> addWidget(log, 12, 0, 2, 8);

    g -> addWidget(ui -> nline,    0, 4, 1, 4);
    g -> addWidget(ui -> ddaline,  1, 4, 1, 4);
    g -> addWidget(ui -> bline,    2, 4, 1, 4);
    g -> addWidget(ui -> bcircle,  3, 4, 1, 4);
    g -> addWidget(ui -> wuline,   4, 4, 1, 4);

    g -> addWidget(ui -> x1, 5, 4, 1, 1, Qt::AlignRight);
    g -> addWidget(ui -> fx, 5, 5, 1, 1);
    g -> addWidget(ui -> y1, 5, 6, 1, 1, Qt::AlignRight);
    g -> addWidget(ui -> fy, 5, 7, 1, 1);

    g -> addWidget(ui -> x2, 6, 4, 1, 1, Qt::AlignRight);
    g -> addWidget(ui -> sx, 6, 5, 1, 1);
    g -> addWidget(ui -> y2, 6, 6, 1, 1, Qt::AlignRight);
    g -> addWidget(ui -> sy, 6, 7, 1, 1);

    g -> addWidget(ui -> r, 7, 4, 1, 1, Qt::AlignRight);
    g -> addWidget(ui -> rad, 7, 5, 1, 1);

    g -> addWidget(ui -> drawButton, 11, 4, 1, 2);
    g -> addWidget(ui -> scaleButton, 11, 6, 1, 2);
    for (int i = 0; i < 8; ++i)
    {
        g -> setColumnStretch(i, 10);
    }
    for (int i = 0; i < 14; ++i)
    {
        g -> setRowStretch(i, 10);
    }
    centralWidget() -> setLayout(g);
    setMinimumSize(500, 600);
    setWindowTitle("Растеризация");
    DisableInput();

    log->AppendMessage("abacaba");
    log->AppendMessage("text");
    log->AppendMessage("abracadabra");
    WuLine(0, 0, 3, 5);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
    delete log;
}
void MainWindow::DisableInput()
{
    ui -> x1 -> setVisible(false);
    ui -> fx -> setVisible(false);
    ui -> y1 -> setVisible(false);
    ui -> fy -> setVisible(false);
    ui -> x2 -> setVisible(false);
    ui -> sx -> setVisible(false);
    ui -> y2 -> setVisible(false);
    ui -> sy -> setVisible(false);
    ui -> r -> setVisible(false);
    ui -> rad -> setVisible(false);
}
void MainWindow::EnableInputLine()
{
    DisableInput();
    ui -> x1 -> setVisible(true);
    ui -> fx -> setVisible(true);
    ui -> y1 -> setVisible(true);
    ui -> fy -> setVisible(true);
    ui -> x2 -> setVisible(true);
    ui -> sx -> setVisible(true);
    ui -> y2 -> setVisible(true);
    ui -> sy -> setVisible(true);
}
void MainWindow::EnableInputCircle()
{
    DisableInput();
    ui -> r -> setVisible(true);
    ui -> rad -> setVisible(true);
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
void MainWindow::WuLine(int x0, int y0, int x1, int y1)
{
    auto ipart = [](qreal x)
    {
        return floor(x);
    };

    auto round = [&ipart](qreal x)
    {
        return ipart(x + 0.5);
    };

    auto fpart = [](qreal x)
    {
        return x - floor(x);
    };

    auto rfpart = [&fpart](qreal x)
    {
        return 1 - fpart(x);
    };

    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    qreal gradient;
    if (dx == 0)
        gradient = 1.0;
    else
        gradient = dy / (qreal)dx;

    // handle first endpoint
    int xend = round(x0);
    qreal yend = y0 + gradient * (xend - x0);
    qreal xgap = rfpart(x0 + 0.5);
    int xpxl1 = xend; // this will be used in the main loop
    int ypxl1 = ipart(yend);
    if (steep)
    {
        area->AddPixel(ypxl1,   xpxl1, rfpart(yend) * xgap);
        area->AddPixel(ypxl1 + 1, xpxl1,  fpart(yend) * xgap);
    }
    else
    {
        area->AddPixel(xpxl1, ypxl1  , rfpart(yend) * xgap);
        area->AddPixel(xpxl1, ypxl1+1,  fpart(yend) * xgap);
    }
    qreal intery = yend + gradient; // first y-intersection for the main loop

    // handle second endpoint
    xend = round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5);
    int xpxl2 = xend; //this will be used in the main loop
    int ypxl2 = ipart(yend);
    if (steep)
    {
        area->AddPixel(ypxl2  , xpxl2, rfpart(yend) * xgap);
        area->AddPixel(ypxl2+1, xpxl2,  fpart(yend) * xgap);
    }
    else
    {
        area->AddPixel(xpxl2, ypxl2,  rfpart(yend) * xgap);
        area->AddPixel(xpxl2, ypxl2+1, fpart(yend) * xgap);
    }

    // main loop
    if (steep)
    {
        for (int x = xpxl1 + 1; x < xpxl2; ++x)
           {
                area->AddPixel(ipart(intery), x, rfpart(intery));
                area->AddPixel(ipart(intery) +1 , x,  fpart(intery));
                intery = intery + gradient;
           }
    }
    else
    {
        for (int x = xpxl1 + 1; x < xpxl2; ++x)
           {
                area->AddPixel(x, ipart(intery),  rfpart(intery));
                area->AddPixel(x, ipart(intery)+1, fpart(intery));
                intery = intery + gradient;
           }
    }
}

void MainWindow::on_bline_clicked()
{
    algo = CurrentAlgo::BresenhamLine;
    EnableInputLine();
}


void MainWindow::on_ddaline_clicked()
{
    algo = CurrentAlgo::DDALine;
    EnableInputLine();
}


void MainWindow::on_bcircle_clicked()
{
    algo = CurrentAlgo::BresenhamCircle;
    EnableInputCircle();
}


void MainWindow::on_nline_clicked()
{
    algo = CurrentAlgo::NaiveLine;
    EnableInputLine();
}

void MainWindow::on_wuline_clicked()
{
    algo = CurrentAlgo::WuLine;
    EnableInputLine();
}

