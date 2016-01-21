/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.cpp
 * Author: fsilva
 * 
 * Created on December 3, 2015, 12:08 PM
 */

#include <iostream>
#include "Message.h"

Message::Message() {}
Message::Message(PB_Eotq::MsgResouces msg, struct sockaddr_in f): l_resources(msg), from(f) {};
Message::Message(const Message& orig) {}
Message::~Message() {}

std::string Message::getRaw() {
    return l_resources.DebugString();
}

std::string Message::unmarshall() {
}

std::string Message::marshall() {
    return raw_msg;
}

struct sockaddr_in Message::getSenderAddr(){
    return from;
}

/*
bool Message::isEmpty() {
    if (msg == "")
        return true;
    return false;
}*/