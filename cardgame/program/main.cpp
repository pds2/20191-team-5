
#include <iostream>
#include <string>
#include <sstream>  
#include <vector>
#include <stdlib.h> 
#include <utility> 
#include <time.h>
#include "httplib.h"
#include "server.h"
#include "deckfactory.h"
#include "card.h"
#include "game.h"
#include "player.h"

using namespace std;

int main(){

    GameServer server;
    server.run();

}

