#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotarea.h"
#include "logwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void BresenhamLine(int x1, int y1, int x2, int y2);
    void BresenhamCircle(int r);
    void DDALine(int x1, int y1, int x2, int y2);
    void NaiveLine(int x1, int y1, int x2, int y2);
    void Castle_Pittwey(int x1, int y1, int x2, int y2);
    void WuLine(int x1, int y1, int x2, int y2);
    //returns transform mask. 1 bit - invert slope, 2 bit - transpose x y
    //int validateLine(int& x1, int& y1, int& x2, int& y2);
    //void transform(int& x, int& y, int mask);
    Ui::MainWindow *ui;
    PlotArea *area = nullptr;
    LogWidget *log = nullptr;
};
#endif // MAINWINDOW_H
