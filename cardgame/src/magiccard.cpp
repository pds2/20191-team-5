#include <magiccard.h>
#include <monstercard.h>

// *CONSTRUTOR
// **construtor padrão
MagicCard::MagicCard() {}

// **construtor com parâmetros
MagicCard::MagicCard(string _description,
                     int _attackDelta,
                     int _defenseDelta,
                     int _lifeDelta,
                     bool _destroy,
                     Target _target) {
  this->description = _description;
  this->attackDelta = _attackDelta;
  this->defenseDelta = _defenseDelta;
  this->lifeDelta = _lifeDelta;
  this->destroy = _destroy;
  this->target = _target;
}

// *MÉTODOS
// **apply: <descrever o que faz>
void MagicCard::apply(Game* game, optional<Position*> position) {
  Player* self = game->getPlayers()[game->getTurn().getPlayerIndex()];
  Player* opponent = game->getPlayers()[!game->getTurn().getPlayerIndex()];

  if (this->attackDelta != 0) {
    MonsterCard* card;
    if (position.value()->isSelf())
      card = self->getField()->at(position.value()->getIndex()).value();
    else
      card = opponent->getField()->at(position.value()->getIndex()).value();
    card->changeAttack(this->attackDelta);
  }
  if (this->defenseDelta != 0) {
    MonsterCard* card;
    if (position.value()->isSelf())
      card = self->getField()->at(position.value()->getIndex()).value();
    else
      card = opponent->getField()->at(position.value()->getIndex()).value();
    card->changeDefense(this->defenseDelta);
  }
  if (this->lifeDelta != 0) {
    if (this->target == NOTARGET || this->target == SELF)
      self->changeLife(this->lifeDelta);
    if (this->target == NOTARGET || this->target == OPPONENT)
      opponent->changeLife(this->lifeDelta);
  }
  if (this->destroy) {
    if (this->target == NOTARGET) {
      MonsterCard::removeFrom(*self->getField()->at(0), self->getField());
      MonsterCard::removeFrom(*self->getField()->at(1), self->getField());
      MonsterCard::removeFrom(*opponent->getField()->at(0),
                              opponent->getField());
      MonsterCard::removeFrom(*opponent->getField()->at(1),
                              opponent->getField());
    } else if (this->target == SELF)
      MonsterCard::removeFrom(
          self->getField()->at(position.value()->getIndex()).value(),
          self->getField());
    else if (this->target == OPPONENT)
      MonsterCard::removeFrom(
          opponent->getField()->at(position.value()->getIndex()).value(),
          opponent->getField());
  }
}

// **getTarget: <descrever o que faz>
Target MagicCard::getTarget() {
  return (this->target);
}

string MagicCard::getDescription() {
  return (this->description);
}