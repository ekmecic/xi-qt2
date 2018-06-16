#pragma once

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QKeyEvent>

class Editor : public QWidget {
  Q_OBJECT

public:
  explicit Editor(QWidget* parent = nullptr);

protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* ev) override;
  void drawTest(QPainter* qp);

private:
  QFont editorFont;
  QVector<QString> lines;
};
