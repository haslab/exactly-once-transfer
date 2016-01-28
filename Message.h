/* 
 * File:   Message.h
 * Author: fsilva
 *
 * Created on December 3, 2015, 12:08 PM
 */

#ifndef MESSAGE_H
#define MESSAGE_H

//#include "Node.h"

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "PB_Eotq.proto3.pb.h"

class Message {
private:
    std::string raw_msg;
    PB_Eotq::MsgResources msg;
    struct sockaddr_in from, to, l_addr, r_addr;
    //Node* from;
    
public:
    Message();
    Message(PB_Eotq::MsgResources msg, struct sockaddr_in f);
    Message(const Message& orig);
    virtual ~Message();
    
    std::string getRaw();
    bool Has_Slot();
    bool Has_Token();
    struct sockaddr_in getSenderAddr();
};

#endif /* MESSAGE_H */

