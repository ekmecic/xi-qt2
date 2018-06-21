#pragma once

#include "rpc_handler.hpp"

// QPlainTextEdit includes QTextFormat which has a Wswitch-default warning.
// This prevents building with Werror, so I've disabled it for now.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <QTextEdit>
#pragma GCC diagnostic pop

#include <QTextCursor>
#include <QTextDocument>

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
