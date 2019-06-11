#include <position.h>

Position::Position(bool self, int index) : self(self), index(index) {}

bool Position::isSelf() {
  return self;
}

int Position::getIndex() {
  return index;
}
