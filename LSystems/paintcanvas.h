#ifndef PAINTCANVAS_H
#define PAINTCANVAS_H

#include <QtWidgets>

class PaintCanvas : public QFrame {
  Q_OBJECT

public:
  PaintCanvas(QWidget *parent = nullptr);
  QPixmap getPixmap();
  void setPixmap(QPixmap pmap);
  void setLinesToDraw(QVector<QLineF> &lines);

public slots:
  void clearArea();

protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);

private:
  QPixmap pixmap;
  QVector<QLineF> linesToDraw;
};

#endif // PAINTCANVAS_H
