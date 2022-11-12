#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout *l = new QHBoxLayout;
    area = new PlotArea();
    l -> addWidget(area);
    l -> addWidget(ui -> frame);
    centralWidget() -> setLayout(l);
    setMinimumSize(500, 500);
    this->setStyleSheet("background-color: white;");
    setWindowTitle("Растеризация");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete area;
}

