#pragma once

#include <QJsonObject>
#include <QMap>
#include <QString>

namespace xi_json {

// Messages sent from xi-qt2 to xi-core
namespace out {
QJsonObject client_started(QString config_dir, QString client_extras_dir);
QJsonObject new_view(QString file_path);
} // namespace out

// Messages sent from xi-core to xi-qt2
namespace in {}
} // namespace xi_json

enum class XiMethod {
  set_style,
  scroll_to,
  update,
  theme_changed,
  config_changed,
  available_plugins,
  plugin_started,
  plugin_stopped,
  update_cmds,
  add_status_item,
  update_status_item,
  remove_status_item,
};

const QMap<QString, XiMethod> xi_method_map = {
    {"set_style", XiMethod::set_style},
    {"scroll_to", XiMethod::scroll_to},
    {"update", XiMethod::update},
    {"theme_changed", XiMethod::theme_changed},
    {"config_changed", XiMethod::config_changed},
    {"available_plugins", XiMethod::available_plugins},
    {"plugin_started", XiMethod::plugin_started},
    {"plugin_stopped", XiMethod::plugin_stopped},
    {"update_cmds", XiMethod::update_cmds},
    {"add_status_item", XiMethod::add_status_item},
    {"update_status_item", XiMethod::update_status_item},
    {"remove_status_item", XiMethod::remove_status_item},
};
