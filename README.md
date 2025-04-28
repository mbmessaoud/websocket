# websocket
test web socket with server and client

Server : use g++ to compile 
g++ -o server server.cpp
exampel of usage 
./server 127.0.0.1 9000

env variable CROW_LOG_LEVEL can be used to set crow debug level

CROW_LOG_LEVEL=Debug ./server 127.0.0.1 9000
CROW_LOG_LEVEL can take the following values : Debug, Info, Warning, Error, Critical see https://crowcpp.org/master/guides/logging/
if CROW_LOG_LEVEL  is not set default log level is Info

Client : https://mbmessaoud.github.io/websocket/
