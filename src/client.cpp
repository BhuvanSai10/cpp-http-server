#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 8080;
const int BUFFER_SIZE = 4096;

int main() {
    // Create TCP socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == -1) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    // Server address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    // Convert IP address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid IP address\n";
        close(clientSocket);
        return 1;
    }

    // Connect to server
    if (connect(clientSocket,
                reinterpret_cast<sockaddr*>(&serverAddress),
                sizeof(serverAddress)) == -1) {
        std::cerr << "Connection failed\n";
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected to server!\n";

    // HTTP Request
    std::string request =
        "GET /about.html HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: MyCPPBrowser/1.0\r\n"
        "Accept: text/html\r\n"
        "Connection: close\r\n"
        "\r\n";

    // Send request
    int bytesSent = send(clientSocket,
                         request.c_str(),
                         request.size(),
                         0);

    if (bytesSent == -1) {
        std::cerr << "Failed to send request\n";
        close(clientSocket);
        return 1;
    }

    std::cout << "\n===== Server Response =====\n\n";

    // Receive complete response
    char buffer[BUFFER_SIZE];

    while (true) {
        int bytesReceived = recv(clientSocket,
                                 buffer,
                                 BUFFER_SIZE - 1,
                                 0);

        if (bytesReceived == 0) {
            // Server closed the connection
            break;
        }

        if (bytesReceived < 0) {
            std::cerr << "Receive failed\n";
            break;
        }

        buffer[bytesReceived] = '\0';
        std::cout << buffer;
    }

    // Close connection
    close(clientSocket);

    std::cout << "\n\nConnection closed.\n";

    return 0;
}