#include <stdint.h>
#include <cstdio> 
#include "AuthData.h"
#include "ImageListData.h"
#include "AckData.h"
#include "StatusData.h"
#include "ImageRequestData.h"
#include "ImageData.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fstream>
#include <netinet/in.h>

using namespace std;
#ifndef MESSAGE_H
#define MESSAGE_H
enum MessageType {  Ping, Auth, StatusReply, ImageListReply, 
                    ImageReply, Ack, NegAck, StatusRequest, ImageListRequest,
                    ViewsRequest, DenyRequest, ImageRequest, ViewsReply, Terminate}; 

class Message
{
    private:
        int messageID, seg_num, seg_tot, size, ownerPort;
        MessageType type;
        string data, ownerIP, flattened;
        static int all_ID;
        const char seperator = ' ';

    public:
        Message();
        Message(const Message& other);
        Message& operator=(const Message& other);
    	Message(MessageType type, string IP, int Port);
        int getID();
        MessageType getType();
    	bool setData(Data &d);
    	void setSeg(int total, int current);

    	string getData();
    	int getSegNum();
    	int getSegTot();
    	int getOwnerPort();
    	string getOwnerIP();
    	int getDataSize();

        void setFlattenedData(string s);

        void setMessageID(int num);
        void setPort(int num);
        void setIP(string s);
        void setType(MessageType mt);
        void setDataSize(int i);
        
        bool Flatten();
        bool unFlatten(string s);
        string getFlattenedMessage();

        void printMessageDetails();

    	~Message();
};
#endif //MESSAGE_H
