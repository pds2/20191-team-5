#pragma once

#include "monstercard.h"
#include "magiccard.h"

class DeckFactory{
    private:
    
    static std::vector<MonsterCard> monsters;
    static std::vector<MagicCard> magicCards;
    static void loadCards();
    DeckFactory();
    
    public:
    
    static std::stack<Card*> getNewDeck();
};