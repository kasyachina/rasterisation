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
    int u = 10; // unit size
    int tick_length = 8;
    int box_offset = 10;
    QColor penColor = Qt::black;
    void inline drawBox(QPainter(&p));
    void inline drawGrid(QPainter& p);
    void inline drawAxis(QPainter& p);
    void inline drawTicks(QPainter& p);
    void inline drawArrows(QPainter& p);
};

#endif // PLOTAREA_H
