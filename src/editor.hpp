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
  void newMsgHandler(const QJsonObject msg);

private:
  void initMenubar();

  QVector<View*> views;
  QFont          editor_font;

  RPCHandler* xi;

#ifdef XI_QT_DEBUG
private slots:
  // When built in debug mode, a special button appears in the menubar that calls this function when pressed
  // This is used for general debugging and prototyping during development
  void debugFunction();
#endif
};
