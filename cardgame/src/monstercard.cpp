#include "monstercard.h"

// *CONSTRUTOR
// **construtor padrão
MonsterCard::MonsterCard(){

}

// **construtor com parâmetros
MonsterCard::MonsterCard(string _name, int _attack, int _defense) : Card(string _name){
    this->attack = _attack;
    this->defense = _defense;
}

// *DESTRUTOR
MonsterCard::~MonsterCard(){

}

// *MÉTODO
// **toggleMode: <descrever o que faz>
Mode MonsterCard::toggleMode(){
    return (this->mode);
}

// **getAttack: <descrever o que faz>
int MonsterCard::getAttack(){
    return(this->attack);
}

// **getDefense: <descrever o que faz>
int MonsterCard::getDefense(){
    return (this->defense);
}

// **getMode: <descrever o que faz>
Mode MonsterCard::getMode(){
    return(this->mode);
}
