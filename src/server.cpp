#include <iostream>
#include <cstring>
#include <thread>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "parser.h"
#include "router.h"

const int PORT = 8080;
const int BUFFER_SIZE = 4096;

//--------------------------------------------------
// Handles one client connection
//--------------------------------------------------
void handleClient(int clientSocket)
{
    char buffer[BUFFER_SIZE];

    int bytesReceived = recv(
        clientSocket,
        buffer,
        BUFFER_SIZE - 1,
        0);

    if (bytesReceived <= 0)
    {
        close(clientSocket);
        return;
    }

    buffer[bytesReceived] = '\0';

    std::cout << "\n========== Request ==========\n";
    std::cout << buffer << std::endl;

    HttpParser parser;
    HttpRequest request = parser.parse(buffer);

    Router router;
    std::string response = router.route(request);

    send(
        clientSocket,
        response.c_str(),
        response.size(),
        0);

    close(clientSocket);

    std::cout << "Response sent to client.\n";
}

//--------------------------------------------------
// Main
//--------------------------------------------------
int main()
{
    int serverSocket;

    sockaddr_in serverAddress;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }

    int opt = 1;

    setsockopt(
        serverSocket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &opt,
        sizeof(opt));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(
            serverSocket,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)) < 0)
    {
        std::cerr << "Bind failed.\n";
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 10) < 0)
    {
        std::cerr << "Listen failed.\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "=====================================\n";
    std::cout << " Multi-threaded HTTP Server Started\n";
    std::cout << " Listening on http://localhost:8080\n";
    std::cout << "=====================================\n";

    while (true)
    {
        sockaddr_in clientAddress;
        socklen_t clientLength = sizeof(clientAddress);

        int clientSocket = accept(
            serverSocket,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientLength);

        if (clientSocket < 0)
        {
            std::cerr << "Accept failed.\n";
            continue;
        }

        std::cout << "\nClient Connected: "
                  << inet_ntoa(clientAddress.sin_addr)
                  << ":"
                  << ntohs(clientAddress.sin_port)
                  << std::endl;

        // Create a new thread for this client
        std::thread worker(handleClient, clientSocket);

        // Let the thread run independently
        worker.detach();
    }

    close(serverSocket);

    return 0;
}