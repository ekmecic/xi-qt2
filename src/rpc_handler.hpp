#pragma once

#include <QJsonObject>
#include <QObject>
#include <QProcess>

class RPCHandler : public QObject {
  Q_OBJECT

public:
  explicit RPCHandler(QObject* parent = nullptr);
  ~RPCHandler();

  // RPC methods
  void sendClientStarted(const QString& config_dir, const QString& client_extras_dir);
  void sendNewView(const QString& file_path);
  void sendToXi(const QJsonObject& object);

signals:
  void newMsg(const QJsonObject& msg);

public slots:
  void handleRPC();

private:
  QProcess* xi_process;
};
