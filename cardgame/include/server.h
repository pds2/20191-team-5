#pragma once
#include <iostream>
#include <string>
#include <sstream>  
#include <vector>
#include <stdlib.h> 
#include <time.h>
#include "httplib.h"
#include "game.h"

using namespace httplib;
using namespace std;
class GameServer{
    
    private: Server httpServer;
    private: pair<int,int> playerIds;
    private: Game game;
    
    vector<string> eventQueue1;
    vector<string> eventQueue2;

    public: GameServer();
    
    public: void enqueeEvent(string event, int playerIndex);

    public: void startGame();
    
    private: vector<string> split(string str, char delimiter);

    private: map<string, string> getParamsMap(string body); 
    
    private: int getPlayerIndexFromID(int playerId);

    public: void run();

};