#include "rpc_handler.hpp"
#include "json_types.hpp"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

RPCHandler::RPCHandler(QObject* parent) : QObject(parent) {
  // Start an instance of xi-core
  this->xi_process = new QProcess(this);
  this->xi_process->setProcessChannelMode(QProcess::MergedChannels);
  this->xi_process->start("xi-core");

  connect(xi_process, &QProcess::readyReadStandardOutput, this, &RPCHandler::handleRPC);
  xi_process->waitForStarted();

  sendDummyJSON();
}

RPCHandler::~RPCHandler() {
  // Stop the process gracefully before destroying everything
  this->xi_process->close();
  delete this->xi_process;
}

void RPCHandler::handleRPC() {
  QByteArray outData = xi_process->readAllStandardOutput();
  qDebug().noquote() << "Reading from Xi:" << QString(outData);
}

void RPCHandler::sendDummyJSON() {
  QJsonDocument doc(xi_json::client_started("/home/emil/tmp", "/home/emil/tmp"));
  QString       json(doc.toJson(QJsonDocument::Compact) + "\n");
  xi_process->write(json.toUtf8());
  qDebug().noquote() << "Writing to Xi:  " << json;
}
