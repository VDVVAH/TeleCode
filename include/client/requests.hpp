#include <curl/curl.h>
#include <json/data_types.hpp>
#include <string>

class Requests {
private:
    std::string proxy;
    unsigned short port;

public:
    Requests();
    Requests(Requests&);
    Requests(Requests&&);
    Requests& operator=(Requests&);
    Requests& operator=(Requests&&);
    ~Requests();

    Json& get(std::string url);
};