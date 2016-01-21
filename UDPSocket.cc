/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDPSocket.cc
 * Author: fsilva
 * 
 * Created on December 17, 2015, 3:08 PM
 */

#include "UDPSocket.h"
#include <cstring>
/* includes for socket communication */
#include <sys/socket.h>
#include <arpa/inet.h>

/* ::: IPv4 ::: 
struct sockaddr_in {
    short            sin_family;    // e.g. AF_INET
    unsigned short   sin_port;      // e.g. htons(3490)
    struct in_addr   sin_addr;      // see struct in_addr, below
    char             sin_zero[8];   // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;           // load with inet_aton()
};
*/

UDPSocket::UDPSocket() {
}

UDPSocket::UDPSocket(const UDPSocket& orig) {
}

UDPSocket::~UDPSocket() {
}

bool UDPSocket::createSocket() {
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc < 0)
        return false;
    return true;            
}

bool UDPSocket::bindSocket(std::string ip_addr="", int p=0) {
    memset((char *) &l_addr, 0, sizeof (l_addr));
    l_addr.sin_family = AF_INET;
    l_addr.sin_addr.s_addr = !ip_addr.empty() ? inet_addr(ip_addr.c_str()) : htonl(INADDR_ANY);
    l_addr.sin_port = htons(p);

    if (bind(sock_desc, (struct sockaddr *) &l_addr, sizeof (l_addr)) < 0)
        return false;
    return true;
}

Message* UDPSocket::listenMessage() {
    socklen_t r_sock_len = sizeof(r_addr);
    int recvlen = recvfrom(sock_desc, buffer, MAX_BUFSIZE, 0, (struct sockaddr *) &r_addr, &r_sock_len);
    if (recvlen > 0) {
        buffer[recvlen] = '\0';
        std::cout << "UDP_RAW_MSG_RECV: " << buffer << std::endl;
        
        /* Unmarshalling msg */
        PB_Eotq::MsgResouces l_resources;
        google::protobuf::io::ArrayInputStream ais(buffer, sizeof(buffer));
        google::protobuf::io::CodedInputStream cis(&ais);
        uint32_t msgSize = 0;
        cis.ReadVarint32(&msgSize);
        google::protobuf::io::CodedInputStream::Limit msgLimit = cis.PushLimit(msgSize);
        l_resources.ParseFromCodedStream(&cis);
        //std::cout << "RAW_MSG_UNMARSHALLED: " << std::endl << l_resources.DebugString() << std::endl;
        
        return new Message(l_resources, r_addr);
    }
    return NULL;
}

bool UDPSocket::sendMessage(std::string m, struct sockaddr_in r_addr) {
    std::string msg = m;
    socklen_t r_sock_len = sizeof(r_addr);
    if (sendto(sock_desc, msg.c_str(), strlen(msg.c_str())+1, 0, (struct sockaddr *) &r_addr, r_sock_len) == -1) {
        std::cout << "[ERROR]: sending to" << std::endl;
        return false;
    }
    return true;
}

struct sockaddr_in UDPSocket::convertIP(std::string& ip_addr, int& p){
    memset((char *) &l_addr, 0, sizeof (l_addr));
    l_addr.sin_family = AF_INET;
    l_addr.sin_addr.s_addr = !ip_addr.empty() ? inet_addr(ip_addr.c_str()) : htonl(INADDR_ANY);
    l_addr.sin_port = htons(p);

    return l_addr;
}
