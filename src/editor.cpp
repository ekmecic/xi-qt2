#include "editor.hpp"

#include <QAction>
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
}

Editor::~Editor() {
  delete this->menubar;
}

void Editor::newView() {
  QString file_name = QFileDialog::getOpenFileName(this, "Open file");
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
}
