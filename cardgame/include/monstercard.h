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

 public:
  MonsterCard();
  MonsterCard(string _name, int _attack, int _defense);
  ~MonsterCard();

  Mode toggleMode();
  void changeAttack(int delta);
  void changeDefense(int delta);
  int getAttack();
  int getDefense();
  Mode getMode();

  virtual void apply(Game& game, std::optional<Position&> position) override;

  static void removeFrom(MonsterCard* card,
                         std::pair<std::optional<MonsterCard*>,
                                   std::optional<MonsterCard*>>& field);
};