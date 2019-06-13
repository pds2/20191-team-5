#pragma once

#include <optional>

#include <card.h>
#include <mode.h>

using namespace std;

class MonsterCard : public Card {
 private:
  int attack;
  int defense;
  Mode mode;

  void removeFrom(std::pair<std::optional<MonsterCard*>,
                            std::optional<MonsterCard*>>& field);

 public:
  MonsterCard();
  MonsterCard(string _name, int _attack, int _defense);
  ~MonsterCard();

  Mode toggleMode();
  int getAttack();
  int getDefense();
  Mode getMode();

  virtual void apply(Game& game, std::optional<Position&> position) override;
};