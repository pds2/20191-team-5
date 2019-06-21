#include <optional>
#include <utility>
#include <sstream>

#include <monstercard.h>
#include <player.h>
#include "target.h"

// *CONSTRUTOR
// **construtor padrão
MonsterCard::MonsterCard() {}

// **construtor com parâmetros
MonsterCard::MonsterCard(string _name, int _attack, int _defense)
    : Card(_name) {
  this->attack = _attack;
  this->defense = _defense;
}

// *DESTRUTOR
MonsterCard::~MonsterCard() {}

// *MÉTODO
// **toggleMode: <descrever o que faz>
Mode MonsterCard::toggleMode() {
  if (this->mode == ATTACK)
    this->mode = DEFENSE;
  else
    this->mode = ATTACK;

  return (this->mode);
}

void MonsterCard::changeAttack(int delta) {
  this->attack += delta;
}

void MonsterCard::changeDefense(int delta) {
  this->defense += delta;
}

// **getAttack: <descrever o que faz>
int MonsterCard::getAttack() {
  return (this->attack);
}

// **getDefense: <descrever o que faz>
int MonsterCard::getDefense() {
  return (this->defense);
}

// **getMode: <descrever o que faz>
Mode MonsterCard::getMode() {
  return (this->mode);
}

void MonsterCard::apply(Game* game, std::optional<Position*> position) {
  int opponentIndex = !game->getTurn().getPlayerIndex();
  Player* opponent = game->getPlayers()->at(opponentIndex);

  // if opponent has cards on field
  if (opponent->getField()->at(0) || opponent->getField()->at(1)) {
    MonsterCard* target =
        opponent->getField()->at(position.value()->getIndex()).value();

    if (target->attack < this->attack) {
      MonsterCard::removeFrom(target, opponent->getField());
      if (target->mode == ATTACK)
        opponent->changeLife(target->attack - this->attack);
    } else {
      Player* player = game->getPlayers()->at(!opponentIndex);
      MonsterCard::removeFrom(this, player->getField());
      player->changeLife(this->attack - target->attack);
    }
  } else
    opponent->changeLife(-this->attack);
}

bool MonsterCard::isSummonable() {
  return true;
}

string MonsterCard::getDescription() {
  std::stringstream descriptionStream;
  descriptionStream << this->name << " atk:" << this->attack << " def:" << this->defense;
  return descriptionStream.str();
}

Target MonsterCard::getTarget() {
  return Target::OPPONENT;
}

void MonsterCard::removeFrom(MonsterCard* card,
                             std::vector<std::optional<MonsterCard*>>* field) {
  if (card == field->at(0).value())
    field->at(0) = std::nullopt;
  else if (card == (*field)[1].value())
    field->at(1) = std::nullopt;
}
