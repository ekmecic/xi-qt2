#pragma once

#include "rpc_handler.hpp"

#include <QTextCursor>
#include <QTextDocument>
#include <QTextEdit>

class Editor : public QTextEdit {
  Q_OBJECT

public:
  explicit Editor(QWidget* parent = nullptr);
  ~Editor();

private:
  QTextDocument* doc;
  QTextCursor*   cursor;
  QFont          editor_font;

  RPCHandler* xi;
};
