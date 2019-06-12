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
    Card(string _name);
    ~Card();

    virtual void apply (Game _game, optional<Position> _position) = 0;
    string getName();
    virtual Target getTarget() = 0;
    virtual string getDescription() = 0;
};

#endif /* PDS2_CARD_H */