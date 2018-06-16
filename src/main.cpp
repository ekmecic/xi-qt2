#include "editor.h"
#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  Widget w;
  Editor editor(&w);

  // Create a vertical layout and add the editor widget to it
  QVBoxLayout vLayout;
  vLayout.setSpacing(0);
  vLayout.setMargin(0);
  vLayout.addWidget(&editor);

  // Create the container layout and add the vertical layout to it
  QVBoxLayout mainLayout;
  mainLayout.addLayout(&vLayout);
  w.setLayout(&mainLayout);

  // Display the window with its child widgets
  w.show();
  editor.show();

  // Set the focus policy for the editor so we can intercept keypresses
  editor.setFocusPolicy(Qt::ClickFocus);

  w.resize(800, 600);

  return app.exec();
}
