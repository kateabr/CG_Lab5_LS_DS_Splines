#include "paintcanvas.h"
#include <queue>

PaintCanvas::PaintCanvas(QWidget *parent) : QFrame(parent) {
  pixmap = QPixmap(this->width(), this->height());
  pixmap.fill();
}

QPixmap PaintCanvas::getPixmap() { return pixmap; }

void PaintCanvas::setPixmap(QPixmap pmap) { pixmap = pmap; }

void PaintCanvas::setLinesToDraw(QVector<QLineF> &lines) {
  linesToDraw.clear();
  linesToDraw = lines;
}

void PaintCanvas::clearArea() {
  pixmap.fill();
  repaint();
}

void PaintCanvas::paintEvent(QPaintEvent *) {
  pixmap.fill();
  QPainter p(this);
  QPainter pp(&pixmap);
  pp.drawLines(linesToDraw);
  p.drawPixmap(0, 0, pixmap);
}

void PaintCanvas::resizeEvent(QResizeEvent *) {
  pixmap = QPixmap(width(), height());
  pixmap.fill();
  repaint();
}
