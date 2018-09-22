#include "view.hpp"

#include <QDebug>

View::View(const QString& file_name, const QString& view_id) {
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
void View::updateView(const xi_json::in::update& current_update) {
  u64              newInvalidBefore = 0;
  u64              newInvalidAfter  = 0;
  u64              oldIndex         = 0;
  QVector<QString> newLines;

  // Iterate over each op in the update message
  for (auto op : current_update.update_ops) {
    switch (op->update_op_type) {
    // Insert the given lines into the text buffer
    case XiUpdateOp::ins: {
      for (auto line : op->lines) {
        newLines.push_back(line);
      }
      break;
    }

    case XiUpdateOp::invalidate: {
      if (newLines.length() == 0) {
        newInvalidBefore += op->num_lines_affected;
      } else {
        newInvalidAfter += op->num_lines_affected;
      }
      break;
    }

    case XiUpdateOp::skip: {
      oldIndex += op->num_lines_affected;
      break;
    }
    case XiUpdateOp::update: {
      u64 nRemaining = op->num_lines_affected;
      if (oldIndex < nInvalidBefore) {
        u64 nInvalid = qMin(op->num_lines_affected, nInvalidBefore - oldIndex);
        if (newLines.length() == 0) {
          newInvalidBefore += nInvalid;
        } else {
          newInvalidAfter += nInvalid;
        }
        oldIndex += nInvalid;
        nRemaining -= nInvalid;
      }

      if (nRemaining > 0 && oldIndex < nInvalidBefore + lines.length()) {
        newInvalidAfter = 0;
        u64 nCopy     = qMin(nRemaining, nInvalidBefore + lines.length() - oldIndex);
        u64 jsonIndex = op->num_lines_affected - nRemaining;
        for (auto line : op->lines) {
          newLines.push_back(line);
          jsonIndex++;
        }
        oldIndex += nCopy;
        nRemaining -= nCopy;
      }

      if (newLines.length() == 0) {
        newInvalidBefore += nRemaining;
      } else {
        newInvalidAfter += nRemaining;
      }
      oldIndex += nRemaining;
      break;
    }

    // Intentional fall-through on all unimplemented update ops
    case XiUpdateOp::copy:
    default:
      // TODO: implement a qDebug operator for the update_op_type
      qInfo() << "Received update op that has no handler yet";
    }
  }
  this->nInvalidBefore = newInvalidBefore;
  this->nInvalidAfter  = newInvalidAfter;
  this->lines          = newLines;

  // this->cursor->setKeepPositionOnInsert(true);
  for (auto line : lines) {
    this->cursor->insertText(line);
  }
}
