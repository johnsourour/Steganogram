#include "Message.h"
#include "UDPSocket.h"
#include "PackGen.h"
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <map>
#include <atomic>
#include <condition_variable>

#ifndef PEER_H
#define PEER_H

enum MessageStatusType{sending, sent, lost};
class Peer
{
    private:
        UDPSocket * udpSocket_client;
        UDPSocket * udpSocket_server;

        thread main_send, main_receive, main_listen, main_pinger;
        int myPort, servicePort;
        char * myHostname, *serviceHostname ;
        string username;

      	std::mutex mutex_1, mutex_2, mutex_3;
        std::condition_variable cond, cond1;

        std::atomic<bool> listening;

        std::vector<std::thread> processes_r, processes_s, request_workers;
        std::queue<Message> requests;
        std::queue<char*> requests_process; 
        std::queue<string> replies;

        std::map<string,MessageStatusType> messageSentStatus; 
        std::map<string,vector<Message> > segmentTable;
        std::map<string,bool> receivedMessageHistory;

        string auth_id;
        
        const int max_size = 50000;

        bool getRequest();
        void listen();
        void processRequest();

        void sendMain();
        void sendHandler(Message msg, int port, char *hostname, int timeout);
        void sendWithoutWaiting(Message m, int port, char *hostname);
        
        void ping();

        void receiveHandler(string message_id, int timeout);
        void handleReceivedMessage(Message m, string id);
        void receiveMain();
        bool logged_in;

    public:
        Peer(char * _listen_hostname, int _listen_port, char* service_hostname, int service_port);
        
        void start();

        bool login(string username, string password);
        void execute(Message msg);

        void halt();

        ~Peer();
};
#endif // PEER_H
