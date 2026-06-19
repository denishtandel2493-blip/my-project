#include <iostream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>

int main() {

    int s = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8083);

    bind(s,(sockaddr*)&addr,sizeof(addr));
    listen(s,5);

    while(true) {

        int c = accept(s,nullptr,nullptr);

        std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n\r\n"
        R"({"message":"Shutdown Command Accepted"})";

        send(c,response.c_str(),response.size(),0);
        close(c);
    }
}
