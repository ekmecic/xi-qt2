#include "rpc_handler.hpp"

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
  QJsonObject object;
  QJsonObject params;
  params["config_dir"]        = "/home/emil/tmp";
  params["client_extras_dir"] = "/home/emil/tmp";
  object["params"]            = params;
  object["method"]            = "client_started";

  QJsonDocument doc(object);
  QString       json(doc.toJson(QJsonDocument::Compact) + "\n");
  xi_process->write(json.toUtf8());
  qDebug().noquote() << "Writing to Xi:  " << json;
}
