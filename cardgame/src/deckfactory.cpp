#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <random>
#include <ctime> 

#include "deckfactory.h"
#include "monstercard.h"

std::vector<MonsterCard> DeckFactory::monsters;
std::vector<MagicCard> DeckFactory::magicCards;

std::stack<Card*> DeckFactory::getNewDeck(){
    if(DeckFactory::monsters.empty() || DeckFactory::magicCards.empty()){
         loadCards();
    }
    std::vector<Card*> allCards;
    for (MonsterCard monster : DeckFactory::monsters) {
        MonsterCard* card = new MonsterCard(monster);
        allCards.push_back(card);
    }
    for (MagicCard magic : DeckFactory::magicCards) {
        MagicCard* card = new MagicCard(magic);
        allCards.push_back(card);
    }

    auto rng = std::default_random_engine {};
    rng.seed(std::time(0));
    std::shuffle(std::begin(allCards), std::end(allCards), rng);

    std::stack<Card*> deck;
    for (Card* card : allCards) deck.push(card);

    return deck;
 }
 
 void DeckFactory::loadCards(){
    std::ifstream monsterDescriptorFile("assets/cardDescriptors/monsters");
    if (monsterDescriptorFile.is_open()) {
        std::string line;
        while (getline(monsterDescriptorFile, line)) {
            vector<string> marshalledCardDetails;
            stringstream ss;
            ss << line.c_str();
            string tok;
             
            while(getline(ss, tok, '|')) {
              marshalledCardDetails.push_back(tok);
            }
            MonsterCard newMonster = MonsterCard(marshalledCardDetails[0], 
                                                 std::stoi(marshalledCardDetails[1]), 
                                                 std::stoi(marshalledCardDetails[2]));
            DeckFactory::monsters.push_back(newMonster);   
        }
        monsterDescriptorFile.close();
    }
    std::ifstream magicCardDescriptorFile("assets/cardDescriptors/magic");
    if (magicCardDescriptorFile.is_open()) {
        std::string line;
        std::map<std::string, Target> targetMap;
        std::map<std::string, bool> boolMap;

        targetMap["NOTARGET"] = Target::NOTARGET;
        targetMap["SELF"] = Target::SELF;
        targetMap["OPPONENT"] = Target::OPPONENT;
        boolMap["false"] = false;
        boolMap["true"] = true;
        while (getline(magicCardDescriptorFile, line)) {
            vector<string> marshalledCardDetails;
            stringstream ss;
            ss << line.c_str();
            string tok;
             
            while(getline(ss, tok, '|')) {
              marshalledCardDetails.push_back(tok);
            }

            MagicCard newMagicCard = MagicCard(marshalledCardDetails[0],
                                               marshalledCardDetails[1],
                                               std::stoi(marshalledCardDetails[2]), 
                                               std::stoi(marshalledCardDetails[3]), 
                                               std::stoi(marshalledCardDetails[4]), 
                                               boolMap[marshalledCardDetails[5]], 
                                               targetMap[marshalledCardDetails[6]]);
            DeckFactory::magicCards.push_back(newMagicCard);   
        }
        magicCardDescriptorFile.close();
    }
 }