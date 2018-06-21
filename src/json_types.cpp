#include "json_types.hpp"

QJsonObject xi_json::client_started(QString config_dir, QString client_extras_dir) {
  QJsonObject return_object_params;
  return_object_params["config_dir"]        = config_dir;
  return_object_params["client_extras_dir"] = client_extras_dir;

  QJsonObject return_object;
  return_object["method"] = "client_started";
  return_object["params"] = return_object_params;

  return return_object;
}
