#include "position.h"

// *CONSTRUTOR
Position::Position(bool _self, int _index){
    this->_self_ = _self;
    this->_index_ = _index;
}

// *DESTRUTOR
Position::~Position(){

}

// *MÉTODOS

// **isSelf: <comentário sobre o que faz>
bool Position::isSelf(){
    return (this->_self_);
}

// **getIndex: <comentário sobre o que faz>
int Position::getIndex(){
    return (this->_index_);
}