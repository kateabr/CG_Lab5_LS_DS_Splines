#include "structure.h"
#include <QtMath>
#include <QtWidgets>

Structure::Structure() {}

void Structure::setAngle(double a) { angle = a; }

void Structure::addToAlphabet(QChar ch) { alphabet.insert(ch); }

void Structure::addToDrawableSymbols(QChar ch) { drawables.insert(ch); }

void Structure::addRule(QChar fr, const QString &to) { rules[fr] = to; }

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

void Structure::levelUp(int lvl) {
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
  currentState = src;
}

void Structure::buildVisualization(QPointF startingPoint, double step) {
  visual.clear();
  processPiece(0, startingPoint, step);
}

void Structure::initCurrentState() { currentState = axiom; }

void Structure::setCyclic(bool c) { cyclic = c; }

void Structure::checkDrawables() {
  if (!drawables.size())
    for (auto ch : alphabet)
      drawables.insert(ch);
}

void Structure::clearStructure() {
  alphabet.clear();
  rules.clear();
  axiom = "";
  drawables.clear();
  currentState = "";
  visual.clear();
  cyclic = true;
}

QVector<QLineF> &Structure::getVisualization() { return visual; }

void Structure::setRandom(bool rand) { random = rand; }

int Structure::processPiece(int ind, QPointF cur, double step) {
  qsrand(time(0));
  double curDistance = 0;
  double curAngle = 0;
  QPointF startingPoint(cur);
  while (ind < currentState.size()) {
    if (currentState[ind] == '+')
      curAngle += random ? qrand() % (int)angle : angle;
    else if (currentState[ind] == '-')
      curAngle -= random ? qrand() % (int)angle : angle;
    else if (currentState[ind] == '[')
      ind = processPiece(ind + 1, cur, step);
    else if (currentState[ind] == ']')
      return ind;
    else if (drawables.contains(currentState[ind])) {
      QPointF newP(cur);
      newP.setX(newP.x() + curDistance * qCos(qDegreesToRadians(curAngle)));
      newP.setY(newP.y() + curDistance * qSin(qDegreesToRadians(curAngle)));
      visual.push_back(QLineF(cur, newP));
      cur = newP;
      curDistance = 0;
      curDistance += step;
    }
    ++ind;
  }
  if (cyclic)
    visual.push_back(QLineF(cur, startingPoint));
  return 0;
}
