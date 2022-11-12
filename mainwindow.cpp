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
    setMinimumSize(500, 500);
    this->setStyleSheet("background-color: white;");
    setWindowTitle("Растеризация");

    log->AppendMessage("abacaba");
    log->AppendMessage("text");
    log->AppendMessage("abracadabra");
    area->AddPixel(1, 1);
    area->AddPixel(3, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
    delete log;
}

