#include "view.hpp"

#include <QDebug>

View::View(QString file_name, QString view_id) {
  this->file_name = file_name;
  this->view_id   = view_id;
  this->doc       = new QTextDocument;
  this->cursor    = new QTextCursor(this->doc);
}

View::~View() {
  delete this->doc;
  delete this->cursor;
}

// Update this view's line cache with the update stuff
void View::updateView(xi_json::in::update& current_update) {
  // Iterate over each op in the update message
  for (auto op : current_update.update_ops) {
    switch (op->update_op_type) {
    // Insert the given lines into the text buffer
    case XiUpdateOp::ins: {
      for (auto line : op->lines) {
        this->cursor->insertText(line);
      }
      break;
    }

    // Intentional fall-through on all unimplemented update ops
    case XiUpdateOp::copy:
    case XiUpdateOp::skip:
    case XiUpdateOp::invalidate:
    case XiUpdateOp::update:
    default:
      // TODO: implement a qDebug operator for the update_op_type
      qInfo() << "Received update op that has no handler yet";
    }
  }
}
