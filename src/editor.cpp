#include "editor.hpp"

#include <QAction>
#include <QMenu>

// Constructor for the editor god widget
Editor::Editor(QWidget* parent) : QTextEdit(parent) {
  // Set the default font to be Fira Mono point size 9
  this->editor_font = QFont("Fira Mono", 9);


  // Initialize the child document object and its cursor
  this->doc    = this->document();
  this->cursor = new QTextCursor(this->doc);

  // Set the default widget font to what was selected above
  this->doc->setDefaultFont(this->editor_font);
  // Initialize the menubar
  this->initMenubar();

  // Start Xi process
  this->xi = new RPCHandler(this);
}

Editor::~Editor() {
  delete this->menubar;
  delete this->doc;
  delete this->cursor;
}

void Editor::newView() {
  this->xi->sendNewView("/home/emil/.zshrc");
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
