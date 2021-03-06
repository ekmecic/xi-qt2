#include "json_types.hpp"

#include <QJsonArray>

QJsonObject xi_json::out::client_started(const QString& config_dir, const QString& client_extras_dir) {
  QJsonObject return_object_params;
  return_object_params["config_dir"]        = config_dir;
  return_object_params["client_extras_dir"] = client_extras_dir;

  QJsonObject return_object;
  return_object["method"] = "client_started";
  return_object["params"] = return_object_params;

  return return_object;
}

QJsonObject xi_json::out::new_view(const QString& file_path) {
  QJsonObject return_object_params;
  return_object_params["file_path"] = file_path;

  QJsonObject return_object;
  return_object["id"]     = 0;
  return_object["method"] = "new_view";
  return_object["params"] = return_object_params;

  return return_object;
}

QJsonObject xi_json::out::scroll(const QString& view_id, const i32& top_line, const i32& bottom_line) {
  QJsonObject return_object_params;
  QJsonArray  line_array          = {top_line, bottom_line};
  return_object_params["method"]  = "scroll";
  return_object_params["params"]  = line_array;
  return_object_params["view_id"] = view_id;

  QJsonObject return_object;
  return_object["method"] = "edit";
  return_object["params"] = return_object_params;

  return return_object;
}

void xi_json::in::new_view_response::read(const QJsonObject& json) {
  this->id      = json["id"].toString();
  this->view_id = json["view_id"].toString();
}

void xi_json::in::update_op::read(const QJsonObject& json) {
  this->update_op_type     = xi_update_op_map[json["op"].toString()];
  this->num_lines_affected = json["n"].toInt();
  for (QJsonValue line : json["lines"].toArray()) {
    QString new_line = QString(line.toObject()["text"].toString());
    this->lines.push_back(new_line);
  }
}

void xi_json::in::update::read(const QJsonObject& json) {
  QJsonObject params = json["params"].toObject();
  QJsonObject update = params["update"].toObject();
  this->view_id      = params["view_id"].toString();
  this->pristine     = update["pristine"].toBool();

  QJsonArray ops = update["ops"].toArray();

  for (QJsonValue op : ops) {
    xi_json::in::update_op* current_op = new xi_json::in::update_op;
    current_op->read(op.toObject());
    this->update_ops.push_back(current_op);
  }
}

xi_json::in::update::~update() {
  for (auto op : this->update_ops) {
    delete op;
  }
}
