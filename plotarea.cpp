#include "plotarea.h"
#include <QPainter>
#include <QPainterPath>
#include <QDialog>

PlotArea::PlotArea(QWidget *parent):QWidget(parent)
{
    u = std::min(width(), height()) / 20;
}

void PlotArea::drawBox(QPainter& p)
{
    int h = height() - 2 * box_offset;
    int w = width() - 2 * box_offset;
    QPen boxPen(boxColor);
    boxPen.setWidth(box_width);
    p.setPen(boxPen);
    p.drawRect(box_offset, box_offset, w, h);
}
void PlotArea::drawGrid(QPainter& p)
{
    QPen gridPen(gridColor);
    gridPen.setWidth(grid_line_width);
    p.setPen(gridPen);
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
void PlotArea::drawAxis(QPainter& p)
{
    QPen axisPen(axisColor);
    axisPen.setWidth(axis_width);
    p.setPen(axisPen);
    p.drawLine(box_offset, zy, width() - box_offset, zy);
    p.drawLine(zx, box_offset, zx, height() - box_offset);
}
void PlotArea::drawTicks(QPainter& p)
{
    QPen ticksPen(axisColor);
    ticksPen.setWidth(axis_width);
    //ticks x
    int i = 0;
    while(zx + (i + 2) * u < width())
    {
        i++;
        p.drawLine(zx + i * u, zy + tick_length, zx + i * u, zy - tick_length);
        p.drawLine(zx - i * u, zy + tick_length, zx - i * u, zy - tick_length);
    }
    //ticks y
    i = 0;
    while(zy + (i + 2) * u < height())
    {
        i++;
        p.drawLine(zx - tick_length, zy + i * u, zx + tick_length, zy + i * u);
        p.drawLine(zx - tick_length, zy - i * u, zx + tick_length, zy - i * u);
    }
}
void PlotArea::drawArrows(QPainter& p)
{
    QPen arrowsPen(axisColor);
    arrowsPen.setWidth((axis_width));
    p.setBrush(QBrush(axisColor));
    p.setRenderHint(QPainter::RenderHint::Antialiasing);
    //arrow x
    QPainterPath px;
    px.moveTo(width() - u - 1, zy + 2 * tick_length);
    px.lineTo(width() - u - 1, zy - 2 * tick_length);
    px.lineTo(width() - 1, zy);
    px.lineTo(width() - u - 1, zy + 2 * tick_length);
    p.drawPath(px);
    //arrow y
    QPainterPath py;
    py.moveTo(zx + 2 * tick_length, u + 1);
    py.lineTo(zx - 2 * tick_length, u + 1);
    py.lineTo(zx, 1);
    py.lineTo(zx + 2 * tick_length, u + 1);
    p.drawPath(py);
}

void PlotArea::drawPixel(int x, int y)
{
    pixels.push_back({x, y});
    repaint();
}
void PlotArea::clear()
{
    pixels.clear();
    repaint();
}
void PlotArea::changeUnit(int nu)
{
    u = nu;
}
void PlotArea::paintEvent(QPaintEvent*)
{
    zx = width() / 2;
    zy = height() / 2;
    QPainter pt(this);
    drawBox(pt);
    drawGrid(pt);
    drawAxis(pt);
    drawTicks(pt);
    drawArrows(pt);
}
