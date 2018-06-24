#pragma once

#include <QTextCursor>
#include <QTextDocument>

class View {
public:
  // Constructures and destructors
  explicit View(QString file_name, QString view_id);
  ~View();

  // Member variables
  QString        file_name;
  QString        view_id;
  QTextDocument* doc;
  QTextCursor*   cursor;
};
