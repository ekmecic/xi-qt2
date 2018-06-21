#pragma once

#include <QObject>

class RPCHandler : public QObject {
  Q_OBJECT

public:
  explicit RPCHandler(QObject* parent = nullptr);
  ~RPCHandler();
};
