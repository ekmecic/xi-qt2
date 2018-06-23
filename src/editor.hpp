#pragma once

#include "rpc_handler.hpp"

#include <QTextCursor>
#include <QTextDocument>
#include <QTextEdit>
#include <QMenuBar>

class Editor : public QTextEdit {
  Q_OBJECT

public:
  explicit Editor(QWidget* parent = nullptr);
  ~Editor();
  QMenuBar* menubar;

private slots:
  void newView();

private:
  void initMenubar();

  QTextDocument* doc;
  QTextCursor*   cursor;
  QFont          editor_font;

  RPCHandler* xi;
};
