#pragma once

#include "json_types.hpp"

#include <QTextCursor>
#include <QTextDocument>

class View {
public:
  // Constructures and destructors
  explicit View(const QString& file_name, const QString& view_id);
  ~View();
  void updateView(const xi_json::in::update& current_update);

  // Member variables
  QString        file_name;
  QString        view_id;
  QTextDocument* doc;
  QTextCursor*   cursor;
};
