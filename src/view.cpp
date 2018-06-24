#include "view.hpp"

View::View(QString file_name, QString view_id) {
  this->file_name = file_name;
  this->view_id   = view_id;
}

View::~View() {}
