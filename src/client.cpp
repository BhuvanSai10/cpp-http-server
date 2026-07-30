#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        std::cerr << "Invalid IP address\n";
        close(clientSocket);
        return 1;
    }

    if (connect(clientSocket,
                reinterpret_cast<sockaddr*>(&serverAddress),
                sizeof(serverAddress)) == -1)
    {
        std::cerr << "Connection failed\n";
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected to server!\n";

    //--------------------------------------------------
    // JSON Body
    //--------------------------------------------------

    std::string body =
        R"({
            "name":"Bhuvan",
            "course":"MTech",
            "age":23
        })";

    //--------------------------------------------------
    // HTTP POST Request
    //--------------------------------------------------

    std::string request =
        "POST /user HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: MyCPPClient/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;

    send(clientSocket,
         request.c_str(),
         request.size(),
         0);

    //--------------------------------------------------
    // Receive Response
    //--------------------------------------------------

    char buffer[4096];

    int bytesReceived =
        recv(clientSocket,
             buffer,
             sizeof(buffer) - 1,
             0);

    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0';

        std::cout << "\n===== Server Response =====\n\n";
        std::cout << buffer << std::endl;
    }

    close(clientSocket);

    return 0;
}