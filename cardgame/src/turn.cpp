#include <turn.h>

Turn::Turn(int playerIndex) {
  this->playerIndex = playerIndex;
  this->summonedMonster = true;
  this->summonedMagic = false;
  this->attacked = std::make_pair(false, false);
}

Phase Turn::getPhase() {
  return this->phase;
}

void Turn::endPhase() {
  phase = static_cast<Phase>(static_cast<int>(phase) + 1);
  if (phase == Phase::End) {
    phase = Phase::Draw;
    playerIndex = (playerIndex + 1) % 2;
    this->summonedMonster = true;
    this->summonedMagic = false;
    this->attacked = std::make_pair(false, false);
  }
}

int Turn::getPlayerIndex() {
  return playerIndex;
}

bool Turn::hasSummonedMonster() {
  return summonedMonster;
}

void Turn::setSummonedMonster() {
  summonedMonster = true;
}

bool Turn::hasSummonedMagic() {
  return summonedMagic;
}

void Turn::setSummonedMagic() {
  summonedMagic = true;
}

bool Turn::hasAttacked(int index) {
  if (index == 0)
    return attacked.first;
  else if (index == 1)
    return attacked.second;
}

void Turn::setAttacked(int index) {
  if (index == 0)
    attacked.first = true;
  else if (index == 1)
    attacked.second = true;
}