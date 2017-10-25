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
  QString levelUp(int lvl);

private:
  QList<QChar> alphabet;
  double angle;
  QMap<QChar, QString> rules;
  QString axiom;
};

#endif // STRUCTURE_H
