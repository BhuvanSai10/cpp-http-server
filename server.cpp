#include <iostream>
#include <cstring>
#include <string>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int main()
{
    // Create TCP socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1)
    {
        cerr << "Socket creation failed!" << endl;
        return 1;
    }

    // Allow port reuse
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Configure server address
    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket,
             (sockaddr *)&serverAddress,
             sizeof(serverAddress)) == -1)
    {
        cerr << "Bind failed!" << endl;
        close(serverSocket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        cerr << "Listen failed!" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "======================================" << endl;
    cout << "HTTP Server Started!" << endl;
    cout << "Listening on port 8080..." << endl;
    cout << "Open http://localhost:8080" << endl;
    cout << "Press Ctrl + C to stop." << endl;
    cout << "======================================" << endl;

    while (true)
    {
        // Accept client
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == -1)
        {
            cerr << "Accept failed!" << endl;
            continue;
        }

        cout << "\nClient Connected!" << endl;

        // Receive request
        char buffer[4096];

        int bytesReceived = recv(
            clientSocket,
            buffer,
            sizeof(buffer) - 1,
            0);

        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';

            cout << "\n========== HTTP REQUEST ==========" << endl;
            cout << buffer << endl;
            cout << "==================================" << endl;
        }

        // HTML page
        string html =
            "<html>"
            "<head><title>My Server</title></head>"
            "<body>"
            "<h1>Hello from My C++ HTTP Server!</h1>"
            "<p>Congratulations! Your server is working.</p>"
            "</body>"
            "</html>";

        // HTTP Response
        string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " +
            to_string(html.length()) +
            "\r\n"
            "Connection: close\r\n"
            "\r\n" +
            html;

        // Send response
        send(
            clientSocket,
            response.c_str(),
            response.length(),
            0);

        cout << "Response Sent!" << endl;

        // Close client socket
        close(clientSocket);

        cout << "Client Disconnected!" << endl;
    }

    close(serverSocket);

    return 0;
}