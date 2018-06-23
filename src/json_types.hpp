#pragma once

#include <QJsonObject>
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
