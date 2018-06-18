#include "editor.h"

#include <QColor>
#include <QDebug>
#include <QRect>
#include <QString>
#include <QVector>

Editor::Editor(QWidget* parent) : QWidget(parent) {
  // Set up Fira Mono as the default editor font, then calculate it's height in px
  this->editorFont = QFont("Fira Mono", 9);
  QFontMetrics fm(this->editorFont);
  uint32_t     editorFontHeight = fm.height();

  // Figure out how many lines we can fit in the window
  int numLines = this->height() / editorFontHeight;
  qDebug() << "this->height(), numLines" << this->height() << numLines;

  // Initialize the buffer with the maximum number of lines
  for (int i = 0; i < numLines; i++) {
    lines.append(Line());
  }
}

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

  // Calculate the height of the font
  qp->setFont(this->editorFont);
  QFontMetrics fm(this->editorFont);
  uint32_t     editorFontHeight = fm.height();

  uint32_t x = 0;
  uint32_t y = editorFontHeight;
  for (auto line : this->lines) {
    qp->drawText(x, y, line.chars);
    y += editorFontHeight;
  }
}

void Editor::keyPressEvent(QKeyEvent* ev) {
  this->lines.append(Line());
  this->lines[0].insertLetter(ev->text());
  qDebug() << ev->key() << ev->text();
  this->repaint();
}

void Editor::handleKeypress(int* key) {
  switch (*key) {
  case Qt::Key_Tab:
    break;
  case Qt::Key_Backspace:
    break;
  case Qt::Key_Return:
    break;
  case Qt::Key_Enter:
    break;
  case Qt::Key_Delete:
    break;
  case Qt::Key_Left:
    break;
  case Qt::Key_Up:
    break;
  case Qt::Key_Right:
    break;
  case Qt::Key_Down:
    break;
  case Qt::Key_Shift:
    break;
  case Qt::Key_Control:
    break;
  case Qt::Key_Meta:
    break;
  case Qt::Key_Alt:
    break;
  case Qt::Key_Space:
    break;
  default:
    break;
  }
}
