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
  void sendClientStarted(QString config_dir, QString client_extras_dir);
  void sendNewView(QString file_path);
  void sendToXi(QJsonObject object);

signals:
  void newMsg(QJsonObject msg);

public slots:
  void handleRPC();

private:
  QProcess* xi_process;
};
