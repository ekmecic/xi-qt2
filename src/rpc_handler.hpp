#pragma once

#include <QObject>
#include <QProcess>

class RPCHandler : public QObject {
  Q_OBJECT

public:
  explicit RPCHandler(QObject* parent = nullptr);
  ~RPCHandler();

public slots:
  void handleRPC();

private:
  QProcess* xi_process;

  void sendClientStarted(QString config_dir, QString client_extras_dir);
  void sendNewView(QString file_path);
  void sendToXi(QJsonObject object);
};
