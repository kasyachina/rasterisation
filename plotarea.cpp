#include "plotarea.h"
#include <QPainter>
#include <QPainterPath>

PlotArea::PlotArea(QWidget *parent):QWidget(parent)
{
}

void PlotArea::drawBox(QPainter& p)
{
    int h = height() - 2 * box_offset;
    int w = width() - 2 * box_offset;
    p.setPen(QPen(QBrush(Qt::gray), box_width));
    p.drawRect(box_offset, box_offset, w, h);
}
void PlotArea::drawGrid(QPainter& p)
{
    QPen gridPen(gridColor);
    gridPen.setWidth(grid_line_width);
    p.setPen(gridPen);
    int zx = width() / 2;
    int zy = height() / 2;
    int i = 0;
    while(zx + i * u <= width() - box_offset)
    {
        i++;
        p.drawLine(zx + i * u, box_offset, zx + i * u, height() - box_offset);
        p.drawLine(zx - i * u, box_offset, zx - i * u, height() - box_offset);
    }
    i = 0;
    while(zy + i * u < height())
    {
        i++;
        p.drawLine(box_offset, zy + i * u, width() - box_offset, zy + i * u);
        p.drawLine(box_offset, zy - i * u, width() - box_offset, zy - i * u);
    }
}
void PlotArea::drawArrows(QPainter& p)
{

}
void PlotArea::drawTicks(QPainter& p)
{

}

void PlotArea::paintEvent(QPaintEvent*)
{
    int zx = width() / 2;
    int zy = height() / 2;
    int tick_width = 4;
    QPainter pt(this);
    drawBox(pt);
    drawGrid(pt);
    pt.setPen(QPen(penColor));
    //axis
    pt.drawLine(u, zy, width() - u, zy);
    pt.drawLine(zx, u, zx, height() - u);
    //ticks x
    int i = 0;
    while(zx + (i + 2) * u < width())
    {
        i++;
        pt.drawLine(zx + i * u, zy + tick_width, zx + i * u, zy - tick_width);
        pt.drawLine(zx - i * u, zy + tick_width, zx - i * u, zy - tick_width);
    }
    //arrow x
        QPainterPath px;
        pt.setBrush(QBrush(penColor));
        pt.setRenderHint(QPainter::RenderHint::Antialiasing);
        px.moveTo(width() - u - 1, zy + 2 * tick_width);
        px.lineTo(width() - u - 1, zy - 2 * tick_width);
        px.lineTo(width() - 1, zy);
        px.lineTo(width() - u - 1, zy + 2 * tick_width);
        pt.drawPath(px);
    //ticks y
    i = 0;
    while(zy + (i + 2) * u < height())
    {
        i++;
        pt.drawLine(zx - tick_width, zy + i * u, zx + tick_width, zy + i * u);
        pt.drawLine(zx - tick_width, zy - i * u, zx + tick_width, zy - i * u);
    }

    //arrow y
        QPainterPath py;
        py.moveTo(zx + 2 * tick_width, u + 1);
        py.lineTo(zx - 2 * tick_width, u + 1);
        py.lineTo(zx, 1);
        py.lineTo(zx + 2 * tick_width, u + 1);
        pt.drawPath(py);
}
