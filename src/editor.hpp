#pragma once

#include "rpc_handler.hpp"
#include "view.hpp"

#include <QMenuBar>
#include <QTextEdit>
#include <QVector>

class Editor : public QTextEdit {
  Q_OBJECT

public:
  explicit Editor(QWidget* parent = nullptr);
  ~Editor();
  QMenuBar* menubar;

private slots:
  void newView();
  void newMsgHandler(QJsonObject msg);

private:
  void initMenubar();

  QVector<View*> views;
  QFont          editor_font;

  RPCHandler* xi;
};
