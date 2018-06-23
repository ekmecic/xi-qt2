#pragma once

#include "global_types.hpp"

#include <QObject>
#include <QTextCursor>
#include <QTextDocument>

class View : public QObject {
  Q_OBJECT

public:
  // Constructures and destructors
  explicit View(u64 view_id, QObject* parent = nullptr);
  ~View();

  // Member variables
  QTextDocument* doc;
  QTextCursor*   cursor;
  u64            view_id;
};
