/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UDPSocket.h
 * Author: fsilva
 *
 * Created on December 17, 2015, 3:08 PM
 */

#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <iostream>
#include "Message.h"
#include <cstring>
#include "PB_Eotq.proto3.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>
/* includes for socket communication */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> /* -> for closing socket */

#define MAX_BUFSIZE 548 // 576 - 8 (udp header) - 20 (ipv4 header) = 548
                        //   NOTE: 14 bytes (ethernet header) --> doesn't count for this


class UDPSocket {
public:
    UDPSocket();
    UDPSocket(const UDPSocket& orig);
    virtual ~UDPSocket();
    
    bool createSocket();
    void closeSocket();
    bool bindSocket(std::string ip_addr, int p);
    Message* listenMessage();
    bool sendMessage(Message &msg, struct sockaddr_in r_addr);
    struct sockaddr_in convertIP(std::string& ip, int& p);
    
private:
    struct  sockaddr_in l_addr, r_addr;
    int     sock_desc;
    char    buffer[MAX_BUFSIZE];

};

#endif /* UDPSOCKET_H */

