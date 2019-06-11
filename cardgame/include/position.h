#pragma once

class Position {
 private:
  bool self;
  int index;

 public:
  /**
   * Position constructor.
   * @param self if the position references the current player's board
   * @param index board index the position references
   */
  Position(bool self, int index);

  /**
   * Returns true if the position references the current player's board.
   */
  bool isSelf();

  /**
   * Returns the board index the position references.
   */
  int getIndex();
};
