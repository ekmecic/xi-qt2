#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <QObject>
#pragma GCC diagnostic pop
#include <QProcess>

class RPCHandler : public QObject {
  Q_OBJECT

public:
  explicit RPCHandler(QObject* parent = nullptr);
  ~RPCHandler();

public slots:
  void commsHandler();

private:
  QProcess* xi_process;

  void sendDummyJSON();
};
