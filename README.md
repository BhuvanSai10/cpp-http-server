# 🚀 NimbusHTTP - Multi-threaded HTTP Server in Modern C++

> A lightweight multi-threaded HTTP server built completely from scratch using **Modern C++17** and **Linux Socket Programming** without using any web frameworks.

![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux-green)
![Build](https://img.shields.io/badge/Build-Make-red)
![License](https://img.shields.io/badge/License-MIT-yellow)

---

# 📖 Overview

NimbusHTTP is a modular HTTP server developed from the ground up to understand how modern web servers work internally.

Instead of relying on frameworks such as Boost.Beast, Crow, Pistache or cpp-httplib, every networking component has been implemented manually using the POSIX socket API.

The project demonstrates how a browser communicates with a server through TCP sockets, how HTTP requests are parsed, how responses are generated, and how multiple clients are served concurrently using a custom thread pool.

This project is designed for learning **Systems Programming**, **Networking**, **Backend Development**, and **Modern C++**.

---

# ✨ Features

## Networking

* TCP Socket Programming
* Client-Server Architecture
* IPv4 Socket Communication
* Socket Creation
* Bind
* Listen
* Accept
* send()
* recv()
* Graceful Socket Shutdown

---

## HTTP

* HTTP/1.1 Request Parsing
* HTTP Response Generation
* HTTP Status Codes
* Header Parsing
* Request Line Parsing
* Custom Response Headers
* Content-Length Handling
* Content-Type Handling

---

## Static File Server

* HTML
* CSS
* JavaScript
* JSON
* Images
* Custom 404 Page
* MIME Type Detection

---

## Dynamic Routing

Supports custom application routes.

Example

```
GET /
GET /about
GET /contact

POST /api/user
POST /api/login
```

---

## JSON APIs

* JSON Request Parsing
* JSON Response Generation
* REST-style API Design

---

## Logging

Every request is logged with

* Timestamp
* Client IP
* HTTP Method
* Requested Path
* HTTP Version
* Status Code
* Response Time

Example

```
2026-07-30 23:15:24 [INFO]
127.0.0.1 GET /index.html HTTP/1.1
-> 200 OK (3 ms)
```

---

## Thread Pool

Instead of creating one thread per client, the server uses a custom fixed-size thread pool.

Benefits

* Reduced thread creation overhead
* Better CPU utilization
* Improved scalability
* Task queue based architecture

---

# 🏗️ Architecture

```
                 Browser

                    │

                 TCP Socket

                    │

                 accept()

                    │

              Thread Pool

                    │

            handleClient()

                    │

             HTTP Parser

                    │

                Router

         ┌──────────┴──────────┐

         │                     │

 Static File Server       JSON API

         │                     │

         └──────────┬──────────┘

                    │

             HttpResponse

                    │

                 send()
```

---

# 📂 Project Structure

```
cpp-http-server/

├── include/

│   ├── file_reader.h
│   ├── http_request.h
│   ├── http_response.h
│   ├── logger.h
│   ├── mime_type.h
│   ├── parser.h
│   ├── router.h
│   └── thread_pool.h
│
├── src/
│   ├── client.cpp
│   ├── file_reader.cpp
│   ├── http_response.cpp
│   ├── logger.cpp
│   ├── mime_type.cpp
│   ├── parser.cpp
│   ├── router.cpp
│   ├── server.cpp
│   └── thread_pool.cpp
├── static/
│   ├── index.html
│   ├── about.html
│   ├── contact.html
│   ├── 404.html
│   ├── style.css
│   └── app.js
│
├── Makefile
└── README.md
```

---

# 🧠 Core Components

## HTTP Parser

Responsible for parsing

* Request Line
* HTTP Headers
* Request Body

Produces an `HttpRequest` object for routing.

---

## Router

Maps incoming requests to

* Static Files
* Dynamic Routes
* REST APIs

Returns an `HttpResponse`.

---

## File Reader

Handles

* Static File Loading
* File Existence Checks

---

## MIME Type Resolver

Automatically determines

```
.html
.css
.js
.png
.jpg
.gif
.ico
.json
.txt
```

and returns the appropriate `Content-Type`.

---

## HTTP Response

Generates complete HTTP responses including

* Status Line
* Headers
* Response Body

---

## Logger

Thread-safe logging utility used throughout the server.

---

## Thread Pool

Implements

* Worker Threads
* Task Queue
* Condition Variables
* Mutex Synchronization

---

# ⚙️ Build Instructions

Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/cpp-http-server.git

cd cpp-http-server
```

Compile

```bash
make
```

Run server

```bash
./server
```

Run client

```bash
./client
```

Clean build

```bash
make clean
```

---

# 🌐 Testing

Start the server

```bash
./server
```

Open your browser

```
http://localhost:8080
```

or use curl

```bash
curl http://localhost:8080
```

Example

```bash
curl http://localhost:8080/about.html
```

---

# 🛠 Technologies Used

* Modern C++17
* POSIX Socket API
* Linux Networking
* GNU Make
* STL
* Multi-threading
* nlohmann/json

---

# 💡 Concepts Implemented

## Networking

* TCP/IP
* Socket Programming
* Client Server Model
* IPv4
* HTTP Protocol
* Request Parsing
* Response Generation

---

## Modern C++

* Object-Oriented Programming
* STL Containers
* std::thread
* std::mutex
* std::condition_variable
* std::chrono
* Lambda Expressions
* RAII Principles
* Modular Design

---

## Concurrency

* Thread Pool
* Producer Consumer Pattern
* Synchronization
* Task Queue
* Mutual Exclusion

---

## Backend Engineering

* Routing
* Static File Serving
* REST APIs
* JSON Handling
* MIME Type Resolution
* Request Logging

---

# 🎯 Skills Demonstrated

* C++17
* Systems Programming
* Linux Programming
* Socket Programming
* TCP/IP Networking
* HTTP Protocol
* REST API Development
* Multithreading
* Concurrent Programming
* File Handling
* Object-Oriented Design
* Software Architecture
* Backend Development

---

# 📈 Future Improvements

* HTTP Keep-Alive
* Query Parameter Parsing
* Cookie Support
* Multipart File Upload
* HTTPS using OpenSSL
* WebSocket Support
* Response Compression (gzip)
* HTTP Caching
* Configuration Files
* CMake Build System
* Unit Testing
* Benchmarking
* epoll-based Event Driven Server

---

# 🎓 Learning Outcomes

Through this project, you will understand

* How browsers communicate with servers
* How HTTP works internally
* How TCP sockets are implemented
* How concurrent servers handle multiple clients
* How REST APIs work without frameworks
* How web servers generate HTTP responses
* How routing systems work
* How thread pools improve scalability
* How production web servers are architected

---

# 📚 References

* RFC 7230 - Hypertext Transfer Protocol (HTTP/1.1)
* POSIX Socket Programming
* Linux Manual Pages
* C++17 Standard Library Documentation

---

# 🤝 Contributing

Contributions, suggestions, and improvements are welcome.

Feel free to fork the repository, create a feature branch, and submit a pull request.

---

# ⭐ Support

If you found this project helpful, consider giving it a ⭐ on GitHub.

It helps others discover the project and motivates further development.

---

# 👨‍💻 Author

**Bhuvan Sai Chowdary**

Integrated M.Tech in Software Engineering

Passionate about

* Systems Programming
* Computer Networks
* Backend Development
* Cloud Native Technologies
* Modern C++

> Built from scratch to understand how web servers work internally.
