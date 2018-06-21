#pragma once

#include <QJsonObject>
#include <QString>

namespace xi_json {
QJsonObject client_started(QString config_dir, QString client_extras_dir);
} // namespace xi_json
