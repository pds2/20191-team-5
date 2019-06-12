#include "magiccard.h"

// *CONSTRUTOR
// **construtor padrão
MagicCard::MagicCard(){

}

// **construtor com parâmetros
MagicCard::MagicCard(string _description, int _attackDelta, int _defenseDelta, int _lifeDelta, bool _destroy, Target _target){
    this->description = _description;
    this->attackDelta = _attackDelta;
    this->defenseDelta = _defenseDelta;
    this->lifeDelta = _lifeDelta;
    this->destroy = _destroy;
    this->target = _target;
}

// *DESTRUTOR
MagicCard::~MagicCard(){

}

// *MÉTODOS
// **apply: <descrever o que faz>
void MagicCard::virtual void apply(Game _game, optional<Position> _position){

}

// **getTarget: <descrever o que faz>
Target MagicCard::getTarget(){
    return (this->target);
}

string MagicCard::getDescription(){
    return (this->description);
}