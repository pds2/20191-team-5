#include <iostream>
#include <string>
#include "httplib.h"

using namespace std;

int main(void)
{
    using namespace httplib;

    Server svr;
    string camarada1;
    string camarada2;

    svr.Get("/hi", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
    });
    
    
    svr.Post("/join", [&](const Request& req, Response& res) {
        if(camarada1.length() == 0){
            camarada1 = req.get_param_value("nome", 0);
        }
        res.set_content(camarada1, "text/plain");
    });


    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
        auto numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
    });

    svr.listen("localhost", 8080);
}