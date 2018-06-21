#pragma once

#include <QPlainTextEdit>
#include <QTextDocument>

class Editor : public QPlainTextEdit {
  Q_OBJECT

public:
  explicit Editor(QWidget* parent = nullptr);
  ~Editor();

private:
  QTextDocument* doc;
  QFont          editorFont;
};
