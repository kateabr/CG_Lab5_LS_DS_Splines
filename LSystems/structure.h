#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <QDebug>
#include <QList>
#include <QMap>
#include <QSet>

class Structure {
public:
  Structure();
  void setAngle(double a);
  void addToAlphabet(QChar ch);
  void addToDrawableSymbols(QChar ch);
  void addRule(QChar fr, const QString &to);
  void setAxiom(const QString &ax);
  void print();
  void levelUp(int lvl);
  void buildVisualization(QPointF startingPoint, double step);
  void initCurrentState();
  void setCyclic(bool c);
  void checkDrawables();
  void clearStructure();
  QVector<QLineF> &getVisualization();

private:
  QSet<QChar> alphabet;
  double angle;
  QMap<QChar, QString> rules;
  QString axiom;
  QSet<QChar> drawables;
  QString currentState;
  QVector<QLineF> visual;
  bool cyclic = true;
  int processPiece(int ind, QPointF cur, double step);
};

#endif // STRUCTURE_H
