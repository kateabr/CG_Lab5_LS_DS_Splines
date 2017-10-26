#include "mainwindow.h"
#include "structure.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->levels, &QSlider::valueChanged, [&](int val) { paint(); });
  connect(ui->startX,
          static_cast<void (QDoubleSpinBox::*)(double)>(
              &QDoubleSpinBox::valueChanged),
          [&](double val) { paint(); });
  connect(ui->startY,
          static_cast<void (QDoubleSpinBox::*)(double)>(
              &QDoubleSpinBox::valueChanged),
          [&](double val) { paint(); });
  connect(ui->step,
          static_cast<void (QDoubleSpinBox::*)(double)>(
              &QDoubleSpinBox::valueChanged),
          [&](double val) { paint(); });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paint() {
  str.levelUp(ui->levels->value());
  str.buildVisualization(QPointF(ui->startX->value(), ui->startY->value()),
                         ui->step->value());
  ui->frame->setLinesToDraw(str.getVisualization());
  ui->frame->repaint();
}

void MainWindow::on_loadFile_clicked() {
  QString filename =
      QFileDialog::getOpenFileName(this, "Load Fractal Preset", "./", "*.frac");
  if (filename.isEmpty())
    return;
  QRegExp rx("(\\ \\|\\ )");
  str.clearStructure();
  QFile inputFile(filename);
  if (inputFile.open(QIODevice::ReadOnly)) {
    QTextStream in(&inputFile);
    QString line = in.readLine();

    while (!in.atEnd()) {
      if (line == "alphabet") {
        line = in.readLine();
        do {
          if (line.size() > 1) {
            QMessageBox::warning(this, "Error", "Invalid alphabet symbol");
            return;
          }
          str.addToAlphabet(line[0]);
          line = in.readLine();
        } while (!line.isEmpty());
      }

      else if (line == "rules") {
        line = in.readLine();
        do {
          QStringList splitLine = line.split(rx);
          if ((splitLine.size() != 2) || (splitLine[0].size() != 1)) {
            QMessageBox::warning(this, "Error", "Invalid rule");
            return;
          }
          str.addRule(splitLine[0][0], splitLine[1]);
          line = in.readLine();
        } while (!line.isEmpty());
      } else if (line == "axiom") {
        line = in.readLine();
        str.setAxiom(line);
      } else if (line == "angle") {
        line = in.readLine();
        double angle = line.toDouble();
        if ((angle < 0) || (angle >= 360)) {
          QMessageBox::warning(this, "Error", "Invalid angle");
          return;
        }
        str.setAngle(angle);
      } else if (line == "drawable") {
        line = in.readLine();
        if (line.size() != 1) {
          QMessageBox::warning(this, "Error", "Invalid drawable symbol");
          return;
        }
        str.addToDrawableSymbols(line[0]);
      } else if (line == "noncyclic") {
        str.setCyclic(false);
      }
      line = in.readLine();
    }

    inputFile.close();
  }
  str.checkDrawables();

  str.initCurrentState();

  paint();
}
