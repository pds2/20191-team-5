#include "card.h"

// *CONSTRUTOR
// **construtor padrão
Card::Card(){

}

// **construtor com parâmetro
Card::Card(string _name){
    this->name = _name;
}

// *DESTRUTOR
Card::~Card(){

}

// *MÉTODOS
// *getName: <descrever o que faz>
string Card::getName(){
    return (this->name);
}
