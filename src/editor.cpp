#include "editor.hpp"
#include "json_types.hpp"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>

// Constructor for the editor god widget
Editor::Editor(QWidget* parent) : QTextEdit(parent) {
  // Set the default font to be Fira Mono point size 9
  this->editor_font = QFont("Fira Mono", 9);

  // Initialize the menubar
  this->initMenubar();

  // Start Xi process
  this->xi = new RPCHandler(this);

  // Delegate any new messages when the RPC receives them
  connect(this->xi, &RPCHandler::newMsg, this, &Editor::newMsgHandler);
}

Editor::~Editor() {
  delete this->menubar;

  // Deallocate each view object
  for (auto view : this->views) {
    delete view;
  }
}

void Editor::newView() {
  // Use a file picker dialog to get the filename
  QString file_name = QFileDialog::getOpenFileName(this, "Open file");
  // Create a new view with a temporary view-id, and append it to the Editor's list
  View* this_view = new View(file_name, "uninitialized");
  this->views.append(this_view);
  // Send the message to xi-core
  this->xi->sendNewView(file_name);
}

void Editor::initMenubar() {
  // Create a nice toolbar
  this->menubar = new QMenuBar(this);

  // Set up the file menu
  QMenu* file_menu = new QMenu("File", this->menubar);

  // Add an "Open file" action that sends a new_view RPC to Xi
  QAction* new_view = new QAction("Open file", file_menu);
  connect(new_view, &QAction::triggered, this, &Editor::newView);
  file_menu->addAction(new_view);
  this->menubar->addMenu(file_menu);

#ifdef XI_QT_DEBUG
  // Add a utility function that triggers an arbitrary action
  QAction* debug_fxn = new QAction("Debug button", file_menu);
  connect(debug_fxn, &QAction::triggered, this, &Editor::debugFunction);
  this->menubar->addAction(debug_fxn);
#endif
}

void Editor::newMsgHandler(const QJsonObject msg) {
  // Handle the xi-core response to new_view
  if (msg["result"].isString()) {
    // Find a view with an uninitialized view-id and assign it this view-id
    for (auto view : views) {
      if (view->view_id == "uninitialized") {
        view->view_id = msg["result"].toString();
      }
    }
    return;
  }

  // Otherwise, it's a "heavier" message from xi and we delegate it to other functions
  // Convert the method string into an enum variant using the method_map QMap
  XiMethod method = xi_method_map[msg["method"].toString()];
  switch (method) {
  case XiMethod::update: {
    // Deserialize the JSON update message into a usable struct
    xi_json::in::update current_update;
    current_update.read(msg);

    // Find the view this message is for
    for (auto view : this->views) {
      if (current_update.view_id == view->view_id) {
        // Update the view with the data from the update
        view->updateView(current_update);
        this->setDocument(view->doc);
      }
    }
    break;
  }
  // Intentional fall-through on all unimplemented methods
  case XiMethod::set_style:
  case XiMethod::scroll_to:
  case XiMethod::theme_changed:
  case XiMethod::config_changed:
  case XiMethod::available_plugins:
  case XiMethod::plugin_started:
  case XiMethod::plugin_stopped:
  case XiMethod::update_cmds:
  case XiMethod::add_status_item:
  case XiMethod::update_status_item:
  case XiMethod::remove_status_item:
  default:
    qInfo() << "Received" << msg["method"].toString() << "method, but no handler exists for it yet";
  }
}

#ifdef XI_QT_DEBUG
void Editor::debugFunction() {
  // Debug button code goes here
}
#endif
