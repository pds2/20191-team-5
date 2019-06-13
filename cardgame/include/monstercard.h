#pragma once

#include <optional>
#include <vector>

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
  /**
   * MonsterCard constructor.
   * @param _name reference the name of the monster
   * @param _attack reference the points of attack of the mosnter
   * @param _defense reference the points of defense of the mosnter
   */
  MonsterCard(string _name, int _attack, int _defense);
  ~MonsterCard();

  /**
   * Toggles the mode between attack and defense
   */
  Mode toggleMode();

  /**
   * Change attack points by a delta.
   * @param delta value difference
   */
  void changeAttack(int delta);

  /**
   * Change defense points by a delta.
   * @param delta value difference
   */
  void changeDefense(int delta);

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
  virtual void apply(Game* game, std::optional<Position*> position) override;

  /**
   * Remove one card from the field.
   * @param card the target card
   * @param field the field from which the card will be removed
   */
  static void removeFrom(MonsterCard* card,
                         std::vector<std::optional<MonsterCard*>>* field);
};
