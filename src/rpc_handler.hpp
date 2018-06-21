#pragma once

#include <QObject>
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
