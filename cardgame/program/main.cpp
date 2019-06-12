#include <iostream>
#include <string>
#include <sstream>  
#include <vector>
#include <stdlib.h> 
#include <time.h>
#include "httplib.h"

using namespace std;


vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
 
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
 
  return internal;
}

map<string, string> getParamsMap(string body){
    auto sep = split(body, ',');
    map<string, string> params; 
    for (auto i = sep.begin(); i != sep.end(); ++i){
        auto keyval = split(*i, '=');
        params[keyval[0]] = keyval[1];
    }
    return params;
}


int main(void){
    using namespace httplib;
    srand (time(NULL));

    Server svr;
    int camarada1 = -1;
    int camarada2 = -1;
    vector<string> eventQueue1;
    vector<string> eventQueue2;
    
    svr.Get("/hi", [](const Request& req, Response& res) {
        cout << "sssss\n";
        res.set_content("Hello World!", "text/plain");
    });
    
    
    svr.Post("/join", [&](const Request& req, Response& res) {
        auto params = getParamsMap(req.body);
        string response = "";
        if(camarada1 == -1){
            camarada1 = rand();
            response = to_string(camarada1);
        } else if(camarada2 == -1){
            camarada2 = rand();
            response = to_string(camarada2);   
        }
        
        cout << params["nome"] << endl;
        res.set_content(response, "text/plain");
    });


    svr.Post("/events", [&](const Request& req, Response& res) {
        auto params = getParamsMap(req.body);
        int playerId = stoi(params["playerId"]);
        vector<string> eventQueue;
        if(camarada1 == playerId){
            eventQueue = eventQueue1;
        } else if(camarada2 == playerId){
            eventQueue = eventQueue2; 
        }
        
        stringstream response;
        for (auto i = eventQueue.begin(); i != eventQueue.end(); ++i){
            response << *i << "|";
        }
        res.set_content(response.str(), "text/plain");
    });

    eventQueue1.push_back("aaaaaa");
    eventQueue1.push_back("aaaaaasdfsdfgfdga");
    
    eventQueue2.push_back("aaaaaa2222222222222");
    eventQueue2.push_back("aaaaaasdfsdfgfdga2222222222222");

    cout << "server up";

    svr.listen("0.0.0.0", 8082);
    
}

