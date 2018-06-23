#include "view.hpp"

View::View(u64 view_id, QObject* parent) : QObject(parent), view_id(view_id) {
  this->view_id = view_id;
  this->doc     = new QTextDocument();
}

View::~View() {
  delete this->doc;
}
