#include "view.hpp"

View::View(QString file_name, u64 view_id) {
  this->file_name = file_name;
  this->view_id   = view_id;
  this->doc       = new QTextDocument();
}

View::~View() {
  delete this->doc;
  delete this->cursor;
}
