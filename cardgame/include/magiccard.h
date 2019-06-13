#pragma once

#include <card.h>

using namespace std;

class MagicCard : public Card {
 private:
  string description;
  int attackDelta;
  int defenseDelta;
  int lifeDelta;
  bool destroy;
  Target target;

 public:
  MagicCard();
  MagicCard(string _description,
            int _attackDelta,
            int _defenseDelta,
            int _lifeDelta,
            bool _destroy,
            Target _target);

  virtual void apply(Game* game, optional<Position*> position);
  virtual Target getTarget();
  virtual string getDescription();
};
