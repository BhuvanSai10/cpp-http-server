#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

#include "parser.h"
#include "router.h"

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1)
    {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket,
             reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) == -1)
    {
        std::cerr << "Bind failed\n";
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Listen failed\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "=====================================\n";
    std::cout << "HTTP Server Started\n";
    std::cout << "Listening on http://localhost:8080\n";
    std::cout << "=====================================\n";

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

        HttpParser parser;
        HttpRequest request = parser.parse(buffer);

        std::cout << "\n========== Parsed Request ==========\n\n";

        std::cout << "Method  : " << request.method << '\n';
        std::cout << "Path    : " << request.path << '\n';
        std::cout << "Version : " << request.version << "\n\n";

        std::cout << "Headers\n";
        std::cout << "-------\n";

        for (const auto& header : request.headers)
        {
            std::cout << header.first
                      << " : "
                      << header.second
                      << '\n';
        }

        Router router;

        std::string response = router.route(request);

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