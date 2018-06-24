#pragma once

#include "global_types.hpp"

#include <QTextCursor>
#include <QTextDocument>

class View {
public:
  // Constructures and destructors
  explicit View(QString file_name, u64 view_id);
  ~View();

  // Member variables
  QString        file_name;
  u64            view_id;
  QTextDocument* doc;
  QTextCursor*   cursor;
};
