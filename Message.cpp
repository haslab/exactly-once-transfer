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

std::string 
Message::getRaw() {
    return msg.DebugString();
}

bool 
Message::hasSlot() {
    return msg.has_slot();
}

bool 
Message::hasToken() {
    return msg.has_token();
}

int 
Message::getNodeId() {
    return msg.from();
}

void 
Message::setNodeId(int id) {
    msg.set_from(id);
}

int 
Message::getNodeSck() {
    return msg.sck();
}

void 
Message::setNodeSck(int sck) {
    msg.set_sck(sck);
}

int 
Message::getNodeDck() {
    return msg.dck();
}

void
Message::setNodeDck(int dck) {
    msg.set_dck(dck);
}

std::string
Message::getNodeVal() {
    return msg.val();
}

void
Message::setNodeVal(std::string v) {
    msg.set_val(v);
}

int 
Message::getNodeSlotSck() {
    PB_Eotq::MsgResources::Map *slot = msg.mutable_slot();
    return slot->sck();
}

int 
Message::getNodeSlotDck() {
    PB_Eotq::MsgResources::Map *slot = msg.mutable_slot();
    return slot->dck();
}

std::string 
Message::getNodeSlotVal() {
    PB_Eotq::MsgResources::Map *slot = msg.mutable_slot();
    return slot->val();
}

void 
Message::setNodeSlot(int s, int d, std::string v) {
    PB_Eotq::MsgResources::Map *slot = msg.mutable_slot();
    slot->set_sck(s);
    slot->set_dck(d);
    slot->set_val(v);
}

int 
Message::getNodeTokenSck() {
    PB_Eotq::MsgResources::Map *token = msg.mutable_token();
    return token->sck();
}

int 
Message::getNodeTokenDck() {
    PB_Eotq::MsgResources::Map *token = msg.mutable_token();
    return token->dck();
}

std::string 
Message::getNodeTokenVal() {
    PB_Eotq::MsgResources::Map *token = msg.mutable_token();
    return token->val();
}

void 
Message::setNodeToken(int s, int d, std::string v) {
    PB_Eotq::MsgResources::Map *token = msg.mutable_token();
    token->set_sck(s);
    token->set_dck(d);
    token->set_val(v);
}

int
Message::getByteSize() {
    return msg.ByteSize();
}

void
Message::setCodedStream(google::protobuf::io::CodedOutputStream *cos) {
    msg.SerializeToCodedStream(cos);
}

struct sockaddr_in 
Message::getSenderAddr(){
    return from;
}