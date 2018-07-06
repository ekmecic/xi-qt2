#pragma once

#include "json_types.hpp"

#include <QTextCursor>
#include <QTextDocument>

class View {
public:
  // Constructures and destructors
  explicit View(QString file_name, QString view_id);
  ~View();
  void updateView(xi_json::in::update& current_update);

  // Member variables
  QString        file_name;
  QString        view_id;
  QTextDocument* doc;
  QTextCursor*   cursor;
};
