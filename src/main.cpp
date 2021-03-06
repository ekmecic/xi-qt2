#include "editor.hpp"

#include <QApplication>
#include <QIcon>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  QWidget      w;
  Editor       editor(&w);

  // Create a vertical layout and add the editor widget to it, then
  // remove the margin around the editor widget
  QVBoxLayout layout(&w);
  layout.addWidget(editor.menubar);
  layout.addWidget(&editor);
  layout.setMargin(0);
  layout.setSpacing(0);

  // Remove the thin blue focus border around the editor widget
  app.setStyleSheet("Editor { outline: 0; }");
  app.setStyleSheet("Editor { border: 0; }");

  // Set the icon of the window to QRC-compiled SVG logo
  app.setWindowIcon(QIcon(":/xi-qt2-logo.svg"));

  // Make sure the window doesn't get too small
  w.setMinimumSize(800, 600);

  // Display the window with its child widgets
  w.show();

  return app.exec();
}
