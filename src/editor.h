#pragma once

#include "line.h"

#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

class Editor : public QWidget {
  Q_OBJECT

public:
  explicit Editor(QWidget* parent = nullptr);

protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* ev) override;
  void drawTest(QPainter* qp);

private:
  void handleKeypress(int* key);

  QVector<Line> lines;
  QFont editorFont;
};
