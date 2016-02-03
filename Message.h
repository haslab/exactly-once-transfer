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
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

class Message {
private:
    std::string raw_msg;
    PB_Eotq::MsgResources::Map slots;
    PB_Eotq::MsgResources::Map tokens;
    struct sockaddr_in from, to, l_addr, r_addr;
    PB_Eotq::MsgResources msg;
    
    //Node* from;
    
public:
    Message();
    Message(PB_Eotq::MsgResources msg, struct sockaddr_in f);
    Message(const Message& orig);
    virtual ~Message();
    
    std::string getRaw();
    bool hasSlot();
    bool hasToken();
    int getNodeId();
    void setNodeId(int id);
    int getNodeSck();
    void setNodeSck(int sck);
    int getNodeDck();
    void setNodeDck(int dck);
    std::string getNodeVal();
    void setNodeVal(std::string v);
    int getNodeSlotSck();
    int getNodeSlotDck();
    std::string getNodeSlotVal();
    void setNodeSlot(int s, int d, std::string v);
    int getNodeTokenSck();
    int getNodeTokenDck(); 
    std::string getNodeTokenVal();
    void setNodeToken(int s, int d, std::string v);
    int getByteSize();
    void setCodedStream(google::protobuf::io::CodedOutputStream *cos);
    
    struct sockaddr_in getSenderAddr();
};

#endif /* MESSAGE_H */

