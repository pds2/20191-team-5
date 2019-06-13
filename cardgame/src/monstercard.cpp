#include <optional>
#include <utility>

#include <monstercard.h>

// *CONSTRUTOR
// **construtor padrão
MonsterCard::MonsterCard() {}

// **construtor com parâmetros
MonsterCard::MonsterCard(string _name, int _attack, int _defense)
    : Card(string _name) {
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

void MonsterCard::apply(Game& game,
                        std::optional<Position&> position) override {
  int opponentIndex = !game.getTurn().getPlayerIndex();
  Player& opponent = game.getPlayers()[opponentIndex];

  // if opponent has cards on field
  if (opponent.getField()[0] || opponent.getField()[1]) {
    MonsterCard* target = opponent.getField()[position->getIndex()];

    if (target->attack < this->attack) {
      MonsterCard::removeFrom(target, opponent.getField());
      if (target->mode == ATTACK)
        opponent.changeLife(target->attack - this->attack);
    } else {
      Player& player = game.getPlayers()[!opponentIndex];
      MonsterCard::removeFrom(this, player.getField());
      player.changeLife(this->attack - target->attack);
    }
  } else
    opponent.changeLife(-this->attack);
}

static void MonsterCard::removeFrom(
    MonsterCard* card,
    std::pair<std::optional<MonsterCard*>, std::optional<MonsterCard*>>&
        field) {
  if (card == field[0].value())
    field[0] = nullptr;
  else if (card == *field[1].value())
    field[1] = nullptr;
}
