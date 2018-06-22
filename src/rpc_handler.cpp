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
  this->xi_process->waitForStarted();

  // Handle any standard output from Xi with the handleRPC function
  connect(xi_process, &QProcess::readyReadStandardOutput, this, &RPCHandler::handleRPC);

  // Tell Xi that there's a new client connected
  sendClientStarted("/home/emil/tmp", "/home/emil/tmp");
}

RPCHandler::~RPCHandler() {
  // Stop the process gracefully before destroying everything
  this->xi_process->close();
  delete this->xi_process;
}

void RPCHandler::handleRPC() {
  QJsonDocument doc = QJsonDocument::fromJson(xi_process->readAllStandardOutput());

#ifdef XI_QT_DEBUG
  QString       pretty_json_str(doc.toJson(QJsonDocument::Indented) + "\n");
  qDebug().noquote().nospace() << "\033[91mRPC Read:\033[0m\n" << pretty_json_str.trimmed();
#endif
}

// Create and send a client_started JSON message
void RPCHandler::sendClientStarted(QString config_dir, QString client_extras_dir) {
  QJsonObject msg = xi_json::client_started(config_dir, client_extras_dir);
  sendToXi(msg);
}

// Create and send a new_view JSON message
void RPCHandler::sendNewView(QString file_path) {
  QJsonObject msg = xi_json::new_view(file_path);
  sendToXi(msg);
}

// Serialize a QJsonObject into a string and send it to Xi's stdin
void RPCHandler::sendToXi(QJsonObject object) {
  // Convert the JSON object to a string
  QJsonDocument doc(object);
  QString       json_str(doc.toJson(QJsonDocument::Compact) + "\n");

  // Send the stringified JSON to Xi
  this->xi_process->write(json_str.toUtf8());

#ifdef XI_QT_DEBUG
  QString pretty_json_str(doc.toJson(QJsonDocument::Indented) + "\n");
  qDebug().noquote().nospace() << "\033[94mRPC Write:\033[0m\n" << pretty_json_str.trimmed();
#endif
}
