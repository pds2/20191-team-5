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
  /**
  * MonsterCard constructor.
  * @param _name reference the name of the monster
  * @param _attack reference the points of attack of the mosnter
  * @param _defense reference the points of _defense of the mosnter
  */
  MonsterCard(string _name, int _attack, int _defense);
  ~MonsterCard();

  /**
  * Toggles the mode between attack and defense
  */
  Mode toggleMode();

  /**
  * Returns the monster's attack points
  */
  int getAttack();

  /**
  * Returns the monster's defense points
  */
  int getDefense();

  /**
  * Returns the monster mode
  */
  Mode getMode();

  /**
  * Execute the attack
  */
  virtual void apply(Game& game, std::optional<Position&> position) override;
};
