#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <QDebug>
#include <QList>
#include <QMap>

class Structure {
public:
  Structure();
  void setAngle(double a);
  void addToAlphabet(QChar ch);
  void addRule(const QChar &fr, const QString &to);
  void setAxiom(const QString &ax);
  void print();
  void levelUp(int lvl);
  void buildVisualization(QPointF startingPoint, double step);
  void initCurrentState();
  QVector<QLineF> &getVisualization();

private:
  QList<QChar> alphabet;
  double angle;
  QMap<QChar, QString> rules;
  QString axiom;
  QString currentState;
  QVector<QLineF> visual;
  int processPiece(int ind, QPointF cur, double step);
};

#endif // STRUCTURE_H
