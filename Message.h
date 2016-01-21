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
    PB_Eotq::MsgResouces l_resources;
    struct sockaddr_in from, to, l_addr, r_addr;
    //Node* from;
    
public:
    Message();
    Message(PB_Eotq::MsgResouces msg, struct sockaddr_in f);
    Message(const Message& orig);
    virtual ~Message();
    
    std::string getRaw();
    std::string unmarshall();
    std::string marshall();
    struct sockaddr_in getSenderAddr();
};

#endif /* MESSAGE_H */

