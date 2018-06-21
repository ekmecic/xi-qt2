#include "editor.h"

// Constructor for the editor god widget
Editor::Editor(QWidget* parent) : QPlainTextEdit(parent) {
  // Set the default font to be Fira Mono point size 9
  this->editorFont = QFont("Fira Mono", 9);

  // Initialize the child document object
  this->doc = this->document();

  // Set the default widget font to what was selected above
  this->doc->setDefaultFont(this->editorFont);
}

Editor::~Editor() {
  delete this->doc;
}
