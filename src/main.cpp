#include "editor.h"

#include <QWidget>
#include <QApplication>
#include <QVBoxLayout>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QWidget w;
  Editor editor(&w);

  // Create a vertical layout and add the editor widget to it, then
  // remove the margin around the editor widget
  QVBoxLayout layout(&w);
  layout.addWidget(&editor);
  layout.setMargin(0);

  // Make sure the window doesn't get too small
  w.setMinimumSize(800, 600);

  // Display the window with its child widgets
  w.show();
  editor.show();

  return app.exec();
}
