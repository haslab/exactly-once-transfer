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
Message::Message(PB_Eotq::MsgResources m, struct sockaddr_in f): msg(m), from(f) {};
Message::Message(const Message& orig) {}
Message::~Message() {}

std::string Message::getRaw() {
    return msg.DebugString();
}

bool Message::Has_Slot() {
    return msg.has_slot();
}

bool Message::Has_Token() {
    return msg.has_token();
}

struct sockaddr_in Message::getSenderAddr(){
    return from;
}