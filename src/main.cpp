#include "editor.h"
#include "mainwindow.h"

#include <QApplication>
#include <QPlainTextEdit>
#include <QVBoxLayout>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  Widget w;
  Editor editor(&w);

  // Make sure the window doesn't get too small
  w.setMinimumSize(800, 600);

  // Create a vertical layout and add the editor widget to it
  QVBoxLayout vLayout;
  vLayout.addWidget(&editor);

  // Create the container layout and add the vertical layout to it
  QVBoxLayout mainLayout;
  mainLayout.addLayout(&vLayout);
  w.setLayout(&mainLayout);

  // Remove all the margins and spacings
  vLayout.setSpacing(0);
  vLayout.setMargin(0);
  mainLayout.setSpacing(0);
  mainLayout.setMargin(0);

  // Display the window with its child widgets
  w.show();
  editor.show();

  return app.exec();
}
