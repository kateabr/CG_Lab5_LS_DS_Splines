#include "structure.h"

Structure::Structure() {}

void Structure::setAngle(double a) { angle = a; }

void Structure::addToAlphabet(QChar ch) { alphabet.push_back(ch); }

void Structure::addRule(const QChar &fr, const QString &to) { rules[fr] = to; }

void Structure::setAxiom(const QString &ax) { axiom = ax; }

void Structure::print() {
  qDebug() << "angle:";
  qDebug() << angle;
  qDebug() << "alphabet:";
  for (auto ch : alphabet)
    qDebug() << ch;
  qDebug() << "rules:";
  for (auto r : rules.keys())
    qDebug() << r << rules.value(r);
  qDebug() << "axiom:";
  qDebug() << axiom;
}

QString Structure::levelUp(int lvl) {
  QString src = axiom;
  QString trg;
  for (int i = 0; i < lvl; ++i) {
    trg = "";
    for (auto ch : src) {
      if (!rules.contains(ch)) {
        trg += ch;
        continue;
      }
      trg += rules[ch];
    }
    src = trg;
  }
  return src;
}
