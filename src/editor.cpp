#include "editor.h"

#include <QColor>
#include <QDebug>
#include <QRect>
#include <QString>
#include <QVector>

Editor::Editor(QWidget* parent) : QWidget(parent) {}

void Editor::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e);

  qDebug() << "pe";

  QPainter qp(this);
  drawTest(&qp);
}

void Editor::drawTest(QPainter* qp) {
  // Draw a white rectangle for a background
  QRect rect(0, 0, this->width(), this->height());
  qp->fillRect(rect, Qt::white);

  QVector<QString> lines;

  QFont editorFont("Fira Mono", 9);
  qp->setFont(editorFont);
  QFontMetrics fm(editorFont);

  uint32_t editorFontHeight = fm.height();
  qDebug() << "editorFontHeight" << editorFontHeight;

  uint32_t x = 0;
  uint32_t y = editorFontHeight;
  for (auto line : this->lines) {
    qp->drawText(x, y, line);
    y += editorFontHeight;
  }
}

void Editor::keyPressEvent(QKeyEvent* ev) {
  this->lines.append(ev->text());
  qDebug() << ev->key() << ev->text();
  this->repaint();
}
