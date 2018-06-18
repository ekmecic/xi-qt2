#include "line.h"

Line::Line() {}

void Line::insertLetter(QString letter) {
  // Strip any unnecessary whitespace
  letter = letter.trimmed();

  // Insert the letter at the proper place
  // Eventually this will correspond to the cursor location, but for now
  // it's just at the end of the line.
  this->chars.append(letter);
}
