#ifndef PDS2_CARD_H
#define PDS2_CARD_H

#include <string>
#include <optional>
#include "target.h"
#include "mode.h"
#include "position.h"
#include "game.h"

using namespace std;

class Card{
protected:
    string name;

public:
    Card();
    /**
     * Card constructor.
     * @param _name reference tha name of the card
     */
    Card(string _name);
    ~Card();

    /**
    * Execute the card, if it is a monster attacks otherwise magic effect
    */
    virtual void apply (Game& _game, optional<Position&> _position) = 0;

    /**
    * Returns the name of the card
    */
    string getName();

    /**
    * Returns the target of the card
    */
    virtual Target getTarget() = 0;

    /**
    * Returns the description of the card
    */
    virtual string getDescription() = 0;
};

#endif /* PDS2_CARD_H */
