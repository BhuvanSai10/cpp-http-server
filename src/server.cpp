#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

#include "parser.h"

int main()
{
    // Create server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1)
    {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    // Server address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(serverSocket,
             reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) == -1)
    {
        std::cerr << "Bind failed\n";
        close(serverSocket);
        return 1;
    }

    // Listen
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Listen failed\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "=====================================\n";
    std::cout << "HTTP Server Started\n";
    std::cout << "Listening on http://localhost:8080\n";
    std::cout << "=====================================\n\n";

    while (true)
    {
        sockaddr_in clientAddress{};
        socklen_t clientLength = sizeof(clientAddress);

        int clientSocket = accept(serverSocket,
                                  reinterpret_cast<sockaddr*>(&clientAddress),
                                  &clientLength);

        if (clientSocket == -1)
        {
            std::cerr << "Accept failed\n";
            continue;
        }

        char buffer[4096];

        int bytesReceived =
            recv(clientSocket,
                 buffer,
                 sizeof(buffer) - 1,
                 0);

        if (bytesReceived <= 0)
        {
            close(clientSocket);
            continue;
        }

        buffer[bytesReceived] = '\0';

        //------------------------------------
        // Parse HTTP Request
        //------------------------------------

        HttpParser parser;

        HttpRequest request = parser.parse(buffer);

        std::cout << "\n========== Parsed Request ==========\n\n";

        std::cout << "Method  : "
                  << request.method
                  << '\n';

        std::cout << "Path    : "
                  << request.path
                  << '\n';

        std::cout << "Version : "
                  << request.version
                  << "\n\n";

        std::cout << "Headers\n";
        std::cout << "-------\n";

        for (const auto& header : request.headers)
        {
            std::cout << header.first
                      << " : "
                      << header.second
                      << '\n';
        }

        //------------------------------------
        // Send Response
        //------------------------------------

        std::string body =
            "<html>"
            "<head><title>My Server</title></head>"
            "<body>"
            "<h1>Hello from My C++ HTTP Server!</h1>"
            "<p>Congratulations! Your server is working.</p>"
            "</body>"
            "</html>";

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " +
            std::to_string(body.size()) +
            "\r\n"
            "Connection: close\r\n"
            "\r\n" +
            body;

        send(clientSocket,
             response.c_str(),
             response.size(),
             0);

        close(clientSocket);

        std::cout << "\nResponse Sent Successfully\n";
        std::cout << "=====================================\n";
    }

    close(serverSocket);

    return 0;
}