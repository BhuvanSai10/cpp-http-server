#include <arpa/inet.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>

#include <sys/socket.h>
#include <unistd.h>

#include "http_response.h"
#include "logger.h"
#include "parser.h"
#include "router.h"
#include "thread_pool.h"

const int PORT = 8080;
const int BUFFER_SIZE = 4096;

//--------------------------------------------------
// Handles one client
//--------------------------------------------------

void handleClient(
    int clientSocket,
    std::string clientIP)
{
    Logger& logger = Logger::getInstance();

    auto startTime =
        std::chrono::high_resolution_clock::now();

    char buffer[BUFFER_SIZE];

    int bytesReceived =
        recv(
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

    HttpParser parser;

    HttpRequest request =
        parser.parse(buffer);

    Router router;

    HttpResponse response =
        router.route(request);

    std::string responseString =
        response.toString();

    send(
        clientSocket,
        responseString.c_str(),
        responseString.size(),
        0);

    auto endTime =
        std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<
            std::chrono::milliseconds>(
                endTime - startTime);

    logger.info(
        clientIP +
        " " +
        request.method +
        " " +
        request.path +
        " " +
        request.version +
        " -> " +
        std::to_string(
            response.getStatusCode()) +
        " " +
        response.getStatusMessage() +
        " (" +
        std::to_string(
            duration.count()) +
        " ms)");

    close(clientSocket);
}

//--------------------------------------------------
// Main
//--------------------------------------------------

int main()
{
    Logger& logger = Logger::getInstance();
    ThreadPool pool(4);

    int serverSocket;

    sockaddr_in serverAddress;

    serverSocket =
        socket(
            AF_INET,
            SOCK_STREAM,
            0);

    if (serverSocket < 0)
    {
        logger.error("Failed to create socket.");
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
        logger.error("Bind failed.");

        close(serverSocket);

        return 1;
    }

    if (listen(serverSocket, 10) < 0)
    {
        logger.error("Listen failed.");

        close(serverSocket);

        return 1;
    }

    std::cout
        << "=====================================\n";

    logger.info(
        "Multi-threaded HTTP Server Started");

    logger.info(
        "Listening on http://localhost:8080");

    std::cout
        << "=====================================\n";

    while (true)
    {
        sockaddr_in clientAddress;

        socklen_t clientLength =
            sizeof(clientAddress);

        int clientSocket =
            accept(
                serverSocket,
                reinterpret_cast<sockaddr*>(&clientAddress),
                &clientLength);

        if (clientSocket < 0)
        {
            logger.error("Accept failed.");
            continue;
        }

        std::string clientIP =
            inet_ntoa(
                clientAddress.sin_addr);

        logger.info(
            "Client Connected : " +
            clientIP);
            
        pool.enqueue(
            [clientSocket, clientIP]()
            {
                handleClient(
                    clientSocket,
                    clientIP);
            });
    }

    close(serverSocket);

    return 0;
}