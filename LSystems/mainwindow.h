#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paintcanvas.h"
#include "structure.h"
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void paint();

private slots:
  void on_loadFile_clicked();

private:
  Ui::MainWindow *ui;
  Structure str;
};

#endif // MAINWINDOW_H
