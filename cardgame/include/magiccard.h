#ifndef PDS2_MAGICCARD_H
#define PDS2_MAGICCARD_H

#include "card.h"

using namespace std;

class MagicCard : public Card
{
private:
    string description;
    int attackDelta;
    int defenseDelta;
    int lifeDelta;
    bool destroy;
    Target target;

public:
    MagicCard();
    MagicCard(string _description, int _attackDelta, int _defenseDelta, int _lifeDelta, bool _destroy, Target _target);
    ~MargicCard();

    virtual void apply (Game _game, optional<Position> _position);
    virtual Target getTarget();
    virtual string getDescription();
};  

#endif /* PDS2_MAGICCARD_H */