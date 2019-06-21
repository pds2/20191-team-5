#include <card.h>
#include <game.h>
#include <monstercard.h>

Game::Game() : turn(Turn(0)) {
  players = new std::vector<Player*>(2);
  players->at(0) = new Player(2000);
  players->at(1) = new Player(2000);
}

void Game::draw() {
  if (turn.getPhase() == Phase::Draw) {
    players->at(turn.getPlayerIndex())->drawCard();
    endPhase();
  }
}

void Game::toggleMode(Position* position) {
  if (turn.getPhase() == Phase::Position) {
    players->at(turn.getPlayerIndex())
        ->getField()
        ->at(position->getIndex())
        .value()
        ->toggleMode();
  }
}

void Game::summon(int cardIndex, std::optional<Position*> target) {
  if (turn.getPhase() == Phase::Summon) {
    auto player = players->at(turn.getPlayerIndex());
    auto hand = player->getHand();
    Card* card = hand->at(cardIndex);
    hand->erase(hand->begin() + cardIndex);
    if (card->isSummonable()) {
      if (!turn.hasSummonedMonster()) {
        if(!player->getField()->at(target.value()->getIndex())){
          player->getField()->at(target.value()->getIndex()) = std::optional<MonsterCard*>();
        }
        player->getField()->at(target.value()->getIndex()) = (MonsterCard*)card;
        turn.setSummonedMonster();
      }
    } else {
      if (!turn.hasSummonedMagic()) {
        card->apply(this, target);
        turn.setSummonedMagic();
      }
    }
  }
}

void Game::attack(Position* monster, std::optional<Position*> target) {
  if (turn.getPhase() == Phase::Battle) {
    if (!turn.hasAttacked(monster->getIndex())) {
      players->at(turn.getPlayerIndex())
          ->getField()
          ->at(monster->getIndex())
          .value()
          ->apply(this, target);
      turn.setAttacked(monster->getIndex());
    }
  }
}

void Game::endPhase() {
  turn.endPhase();
}

std::vector<Player*>* Game::getPlayers() {
  return players;
}

Turn Game::getTurn() {
  return turn;
}
