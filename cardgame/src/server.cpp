#include <iostream>
#include <string>
#include <sstream>  
#include <vector>
#include <stdlib.h> 
#include <time.h>
#include "httplib.h"
#include "server.h"
#include "game.h"
#include "card.h"
#include "monstercard.h"

void GameServer::startGame(){
    enqueeEvent("ENEMYCONNECTED", this->playerIds.first);
    enqueeEvent("ENEMYCONNECTED", this->playerIds.second);
    this->game.draw();
    this->game.endPhase();
}

void GameServer::enqueeEvent(string event, int playerId){
    vector<string> *eventQueue;
    if(playerIds.first == playerId){
        eventQueue = &(this->eventQueue1);
    } else if(playerIds.second == playerId){
        eventQueue = &(this->eventQueue2); 
    }
    eventQueue->push_back(event);
}

int GameServer::getPlayerIndexFromID(int playerId){
    int playerIndex = -1;
    if(playerIds.first == playerId){
        playerIndex = 0;
    } else if(playerIds.second == playerId){
        playerIndex = 1; 
    }
    return playerIndex;
}

GameServer::GameServer(){
    srand (time(NULL));
        
        playerIds.first = -1;
        playerIds.second = -1;
        
        httpServer.Post("/join", [&](const Request& req, Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            auto params = getParamsMap(req.body);
            string response = "";
            if(playerIds.first == -1){
                playerIds.first = rand();
                response = to_string(playerIds.first);
            } else if(playerIds.second == -1){
                playerIds.second = rand();
                startGame();
                response = to_string(playerIds.second);   
            }
            
            cout << "ID: " << response << endl;
            res.set_content(response, "text/plain");
        });
        
        httpServer.Post("/getHand", [&](const Request& req, Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            auto params = getParamsMap(req.body);
            int playerIndex = getPlayerIndexFromID(stoi(params["playerId"]));
            auto hand = this->game.getPlayers()->at(playerIndex)->getHand();
            stringstream response;
            for (int i = 0; i < hand->size(); i++) {
                Card* card = hand->at(i);
                response << card->getName() << "," << card->getDescription() << "|";
            }
            res.set_content(response.str(), "text/plain");
        });
    
        httpServer.Post("/events", [&](const Request& req, Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            auto params = getParamsMap(req.body);
            int playerId = stoi(params["playerId"]);
            vector<string> *eventQueue;
            if(playerIds.first == playerId){
                eventQueue = &(eventQueue1);
            } else if(playerIds.second == playerId){
                eventQueue = &(eventQueue2); 
            }
            
            stringstream response;
            for (auto i = eventQueue->begin(); i != eventQueue->end(); ++i){
                response << *i << "|";
            }
            res.set_content(response.str(), "text/plain");
            eventQueue->clear();
        });
        
        httpServer.Post("/summon", [&](const Request& req, Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            auto params = getParamsMap(req.body);
            int playerId = stoi(params["playerId"]);
            int playerIndex = getPlayerIndexFromID(playerId);
            if(game.getTurn().getPlayerIndex() == playerIndex){
                int cardIndex = stoi(params["index"]);
                std::optional<Position*> target = new Position(true, cardIndex); 
                game.summon(cardIndex, target);
                int enemyPlayerID = (playerId == this->playerIds.first ? this->playerIds.second : this->playerIds.second);  
                enqueeEvent("ENEMYSUMMONEDMONSTER", enemyPlayerID);
                res.set_content("success", "text/plain");
            }
        });
        
        httpServer.Post("/getField", [&](const Request& req, Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            auto params = getParamsMap(req.body);
            int playerIndex = getPlayerIndexFromID(stoi(params["playerId"]));
            string which = params["which"];
            playerIndex = which == "enemy" ? !playerIndex : playerIndex; 
            auto field = this->game.getPlayers()->at(playerIndex)->getField();
            stringstream response;
            for (int i = 0; i < field->size(); i++) {
                if(field->at(i)){
                    MonsterCard* card = field->at(i).value();
                    response << card->getName() << "," << card->getDescription() << "|";
                }
            }
            res.set_content(response.str(), "text/plain");
        });
        
        httpServer.set_base_dir("./");
    
}


vector<string> GameServer::split(string str, char delimiter) {
      vector<string> internal;
      stringstream ss(str); // Turn the string into a stream.
      string tok;
     
      while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
      }
     
      return internal;
    }
    
map<string, string> GameServer::getParamsMap(string body){
        auto sep = split(body, ',');
        map<string, string> params; 
        for (auto i = sep.begin(); i != sep.end(); ++i){
            auto keyval = split(*i, '=');
            params[keyval[0]] = keyval[1];
        }
        return params;
}

void GameServer::run(){
    httpServer.listen("0.0.0.0", 8082);
}