#pragma once

#include "global_types.hpp"

#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QVector>

// Possible methods sent by xi-core
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

// Maps a string to the corresponding XiMethod for use in switch statements
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

// Possible operations of an update method
enum class XiUpdateOp {
  copy,
  skip,
  invalidate,
  update,
  ins,
};

// Maps a string to the corresponding XiUpdateOp for use in switch statements
const QMap<QString, XiUpdateOp> xi_update_op_map = {
    {"copy", XiUpdateOp::copy},
    {"skip", XiUpdateOp::skip},
    {"invalidate", XiUpdateOp::invalidate},
    {"update", XiUpdateOp::update},
    {"ins", XiUpdateOp::ins},
};

// Messages sent from xi-qt2 to xi-core
namespace xi_json::out {
QJsonObject client_started(const QString& config_dir, const QString& client_extras_dir);
QJsonObject new_view(const QString& file_path);
} // namespace xi_json::out

// Messages sent from xi-core to xi-qt2
namespace xi_json::in {
// xi-core's response to the xi-qt2's new_view RPC
typedef struct new_view_response {
  QString id;
  QString view_id;
  void    read(const QJsonObject& json);
} new_view_response;

// Deserialized form of an update operation
// Copied verbatim from Xi RPC spec and adapted to Qt
typedef struct update_op {
  XiUpdateOp       update_op_type;
  u64              num_lines_affected;
  QVector<QString> lines;
  void             read(const QJsonObject& json);
} update_op;

// Deserialized form of the update XiMethod
// Copied verbatim from Xi RPC spec and adapted to Qt
typedef struct update {
  QString             view_id;
  bool                pristine;
  QVector<update_op*> update_ops;
  void                read(const QJsonObject& json);
  ~update();
} update;
} // namespace xi_json::in
