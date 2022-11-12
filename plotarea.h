#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QPainter>
#include <QWidget>

class PlotArea : public QWidget
{
    Q_OBJECT
public:
    explicit PlotArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
private:
    int u = 20; // unit size
    int tick_length = 4;
    int grid_line_width = 1;
    int axis_width = 2;
    int box_offset = 1;
    int box_width = 1;
    int zx = 0;
    int zy = 0;
    QColor axisColor = Qt::black;
    QColor gridColor = Qt::gray;
    QColor boxColor = Qt::gray;
    void inline drawBox(QPainter(&p));
    void inline drawGrid(QPainter& p);
    void inline drawAxis(QPainter& p);
    void inline drawTicks(QPainter& p);
    void inline drawArrows(QPainter& p);
};

#endif // PLOTAREA_H
