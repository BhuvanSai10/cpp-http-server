#include <arpa/inet.h>
#include <cstring>
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
        std::cerr << "Invalid address\n";
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
    // POST Body
    //--------------------------------------------------

    std::string body = "Hello from Client";

    //--------------------------------------------------
    // Build POST Request
    //--------------------------------------------------

    std::string request =
        "POST /echo HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: MyCPPBrowser/1.0\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;

    //--------------------------------------------------
    // Send Request
    //--------------------------------------------------

    send(clientSocket,
         request.c_str(),
         request.size(),
         0);

    //--------------------------------------------------
    // Receive Response
    //--------------------------------------------------

    char buffer[4096];

    int bytesReceived = recv(
        clientSocket,
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