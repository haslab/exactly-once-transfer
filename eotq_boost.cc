/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   eotq.cc
 * Author: fsilva
 *
 * Created on 10 November 2015, 21:46
 */

#include <cstdlib>
#include <map>
#include <iostream>
#include <string>
#include <unistd.h>         /* for sleep/usleep */
#include "Message.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include <vector>
#include <boost/algorithm/string/trim.hpp>
#include <boost/thread.hpp>

using namespace std;

#define START_LST_PORT  8000    // 1st port to start listen
#define NUM_NODES       10      // number of nodes to spawn

float zero() {
    return 0;
}

float oplus (const float &a, const float &b) {
  return a + b;
}

int oplus (const int &a, const int &b) {
  return a + b;
}

float needs (const float &a, const float &b)
{
  return (b-a+abs(b-a))/4;
}

int needs (const int &a, const int &b)
{
  return (b-a+abs(b-a))/4;
}

template<typename T>
class Eotq {
public:
    T val;
    int id;
    int sck;
    int dck;
    int port;
    
    map < int, pair<pair<int, int>, T> > slots;
    map < int, pair<pair<int, int>, T> > tokens;

    /* CONSTRUCTOR */
    Eotq(int i=0, int p=0, T v=zero()) {
        id  = i;
        val = v;
        sck = 0;
        dck = 0;
        port= p;
        
        /* Spawn listening thread */
        //boost::thread th_listen(startListening);
        //startListening();
    }
    
    void plus(T v)
    {
        val = oplus(val, v);
    }
    
    unsigned int numTokens() {
        return tokens.size();
    }

    unsigned int numSlots() {
        return slots.size();
    }

    /* parse the output to screen */
    friend ostream &operator<<(ostream &output, const Eotq &o) {
        output << "id: " << o.id << " val: " << o.val <<
                  " sck: " << o.sck << " dck: " << o.dck << endl;
        typename map < int, pair<pair<int, int>, T> >::const_iterator it;
        for (it = o.slots.begin(); it != o.slots.end(); it++) {
            output << "SLOT: ( " << it->first 
                   << ", [sck:" << it->second.first.first << ", dck: " << it->second.first.second << "], "
                   << it->second.second << ")"<< endl;
        }
        for (it = o.tokens.begin(); it != o.tokens.end(); it++) {
            output << "TOKEN: ( " << it->first 
                   << ", [sck:" << it->second.first.first << ", dck: " << it->second.first.second << "], "
                   << it->second.second << ")"<< endl;
        }
        return output;
    }
	
    void createSlot(Eotq<T> &j) 
    {
        typename map < int, pair<pair<int, int>, T> >::iterator its = slots.find(id);
        
        if ( its == slots.end() )
        {
            T hint;
            hint = needs(val, j.val);
            //cout << "VAL_1=" << val << " :: VAL_2=" << j.val << " :: H=" << hint << endl;
            if ( hint != zero()) {
                slots[j.id] = make_pair(make_pair(j.sck, dck), hint);
                dck++;
            }
        }
    }
    
    void startListening() 
    {
        UDPSocket udp;
        Message *msg_rcv;
        if (udp.createSocket()) {
            //cout << "[SUCCESS]: Creating socket." << endl;
            if (udp.bindSocket("", port)) {
                cout << "[SUCCESS]: Binded on port " << port << endl;
                for (;;) {
                    if ((msg_rcv = udp.listenMessage()) != NULL) {
                        //cout << "RAW_MSG_RECV: " << msg->getRaw() << endl;
                        /* Initialization for testing */
                        val = 4;
                        dck = 20;
                        /* END Initialization */
                        stringstream sstream(msg_rcv->getNodeVal());
                        Eotq<T> r_node(msg_rcv->getNodeId());
                        r_node.sck = msg_rcv->getNodeSck();
                        r_node.dck = msg_rcv->getNodeDck();
                        sstream >> r_node.val;
                        if ( msg_rcv->hasSlot() ) {
                            r_node.slots[msg_rcv->getNodeId()] = make_pair(make_pair(msg_rcv->getNodeSlotSck(), msg_rcv->getNodeSlotDck()), 0);
                            sstream.str(std::string());
                            sstream.clear();
                            sstream.str(msg_rcv->getNodeSlotVal());
                            sstream >> r_node.slots[msg_rcv->getNodeId()].second;
                        }
                        if ( msg_rcv->hasToken() ) {
                            r_node.tokens[msg_rcv->getNodeId()] = make_pair(make_pair(msg_rcv->getNodeTokenSck(), msg_rcv->getNodeTokenDck()), 0);
                            sstream.str(std::string());
                            sstream.clear();
                            sstream.str(msg_rcv->getNodeTokenVal());
                            sstream >> r_node.tokens[msg_rcv->getNodeId()].second;
                        }   
                        createSlot(r_node);
                        //cout << r_node << endl;
                        
                        /* PREPARING TO SEND REPLY MESSAGE*/
                        Message msg_reply;
                        msg_reply.setNodeId(id);
                        msg_reply.setNodeSck(sck);
                        msg_reply.setNodeDck(dck);
                        sstream.str(std::string());
                        sstream.clear();
                        sstream << val;
                        msg_reply.setNodeVal(sstream.str());
                        
                        typename map < int, pair<pair<int, int>, T> >::const_iterator it;
                        for (it = slots.begin(); it != slots.end(); it++) {
                            if (it->first == r_node.id)
                            {
                                sstream.str(std::string());
                                sstream.clear();
                                sstream << it->second.second;
                                msg_reply.setNodeSlot(it->second.first.first, it->second.first.second, sstream.str());
                            }
                        }
                        for (it = tokens.begin(); it != tokens.end(); it++) {
                            if (it->first == r_node.id)
                            {
                                sstream.str(std::string());
                                sstream.clear();
                                sstream << it->second.second;
                                msg_reply.setNodeToken(it->second.first.first, it->second.first.second, sstream.str());
                            }
                        }
                        
                        UDPSocket udp_send;
                        if (udp_send.createSocket()) {
                            if (udp_send.bindSocket("", 0)) {
                                udp_send.sendMessage(msg_reply, msg_rcv->getSenderAddr());
                                udp_send.closeSocket();
                            }
                        }
                        
                    }
                  }
            } 
            else {
                cout << "[ERROR]: Trying to binding." << endl;
                //return 1;
            }

        } else {
            cout << "[ERROR]: Creating socket." << endl;
            //return 2;
        }
    }
    
    /*
    void prepareSpamming() 
    {
        /* for each neighbor
        for(;;)
        {
            boost::thread k(boost::bind(&Eotq<int>::spamResources, this));
            k.detach();
            boost::this_thread::sleep(boost::posix_time::seconds(3));
        }
    }
    */
    
    void annouceResourcesToNeighbor(string neigh_ip_addr, int neigh_port)
    {
        cout << "FROM: " << id << ":" << port << " start spam: " << val << endl;
        cout << "TO: " << neigh_ip_addr << ":" << neigh_port << endl;
        /*
        UDPSocket udp;
        
        if (udp.bindSocket("", 0)) 
        {
            cout << "[SUCCESS]: Binded on port " << port << endl;
            udp.sendMessage("TESTE"+val , udp.convertIP(neigh_ip_addr, neigh_port));
        }
        else 
        {
            cout << "[ERROR]: Trying to binding." << endl;
            //return 1;
        }*/
        
    }
    
    void testThread()
    {
        for(;;)
        {
            cout << id << ":" << port << " -> " << val << endl;
            sleep(2);
        }
    }
};

class Node
{
private:
public:    
    int port;
    string ip_addr;
    Node(string ip="127.0.0.1", int p=0): ip_addr(ip), port(p) {};
};

/* Starting with global declarations */
vector< Eotq<int> > nodes(NUM_NODES);
vector< Node > neighbors(NUM_NODES);

vector<string> splitOptString(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void brokerThread(string ip_addr="", int port=0)
{   
    int sock_desc, r_sock, c, read_size;
    struct sockaddr_in l_addr, r_addr;
    char buffer[MAX_BUFSIZE];
     
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0)
    {
        cout << "[ERROR]: Creating socket. Exiting thread. " << endl;
    }
    else
    {
        memset((char *) &l_addr, 0, sizeof (l_addr));
        l_addr.sin_family = AF_INET;
        l_addr.sin_addr.s_addr = !ip_addr.empty() ? inet_addr(ip_addr.c_str()) : htonl(INADDR_ANY);
        l_addr.sin_port = htons(port);

        int val = 1;
        setsockopt(sock_desc, SOL_SOCKET,SO_REUSEADDR, &val, sizeof(int));

        if (bind(sock_desc, (struct sockaddr *) &l_addr, sizeof (l_addr)) < 0)
        {
            cout << "[ERROR]: Binding socket." << endl;
            shutdown(sock_desc, 0);
        }
        else
        {

            listen(sock_desc , 3); // accepts a max of 3 simultaneous connections
            c = sizeof(struct sockaddr_in);

            if ( (r_sock = accept(sock_desc, (struct sockaddr *)&r_addr, (socklen_t*)&c)) < 0)
            {
                cout << "[ERROR]: Accepting socket connection." << endl;
                shutdown(sock_desc, 0);
            }
            else
            {
                //Receive a message from client
                while( (read_size = recv(r_sock , buffer , MAX_BUFSIZE , 0)) > 0 )
                {
                    vector<string> ops;
                    buffer[read_size-2] = '\0'; //deleting carriage return from buffer and other char from buffer
                    string buf(buffer);
                    transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
                    ops = splitOptString(buf, ',');
                    /*
                     ops [0] => primary operation
                         [1] => primary node
                         [2] => secondary operation
                         [3] => secondary node
                    */
                    //cout << "[0]:" << ops[0] << " ::: [1]: " << ops[1] << "::: [2]: " << ops[2] <<endl;

                    if ( ops[0] == "p" )
                    {
                        // print node data
                        stringstream reply;
                        reply << "----Reply----" << endl << nodes[atoi(ops[1].c_str())];
                        write(r_sock , reply.str().c_str() , reply.str().length());
                    }
                    else if ( ops[0] == "+" )
                    {
                        // add resources
                        nodes[atoi(ops[1].c_str())].plus(atoi(ops[2].c_str()));

                        stringstream reply;
                        reply << "\tReply: " << nodes[atoi(ops[1].c_str())];
                        write(r_sock , reply.str().c_str() , reply.str().length());
                    } 
                    else if ( ops[0] == "done")
                    {
                        cout << "[INFO]: Client disconnected." << endl;

                        stringstream reply;
                        reply << "\tReply: " << "Bye bye ... " << endl;
                        write(r_sock , reply.str().c_str() , reply.str().length());

                        shutdown(sock_desc, 0);
                        break;
                        //return 0;
                    }
                    else
                    {
                        cout << "[WARNING]: Unknown operation => " << ops[0] << endl;
                    }

                }
            }
        }
    }
}

void InitializeNodes()
{
    cout << "Starting Nodes ..." << endl;
    cout << "SIZE_Nodes: " << nodes.size() << endl;
    cout << "SIZE_Neighbors: " << neighbors.size() << endl;
    /* Initialize base values values to nodes (if needed) */
    for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
        nodes[i].id     = i;
        nodes[i].port   = START_LST_PORT + i;
        nodes[i].val    = 20+i;
    }
    
    for(vector<int>::size_type i = 0; i != neighbors.size(); i++) {
        neighbors[i].port    = nodes[i].port;
    }
    
    //nodes[0].annouceResourcesToNeighbor("127.0.0.1", 8888);
    
    /* Create initial socket for listening*/    
    for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
        //boost::thread nodeListen(boost::bind(&Eotq<int>::testThread, &nodes[i]));
        boost::thread t(boost::bind(&Eotq<int>::startListening, &nodes[i]));
    }
    
    /* Test to verify shared mem between threads in each EOTQ class
    for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
        boost::thread nodeListen(boost::bind(&Eotq<int>::testThread, &nodes[i]));
    }
    sleep(2);
    for (int i=0; i<= 100 ; i++)
    {
        for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
            nodes[i].plus(10);
        }
        sleep(1);
    }*/
    
    /* Create initial socket for spamming node resources */
    /*for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
        boost::thread t(boost::bind(&Eotq<int>::prepareSpamming, &nodes[i]));
    }*/
    
    
    /* Broker thread */
    boost::thread broker(boost::bind(brokerThread, "", 7000));
    broker.detach();
    //cout << "Waiting for clients to join." << endl;
    //broker.join();
    //cout << "end join" << endl;
}

void test1() {
//    cout << "----------------------< Starting >----------------------" << endl;
//    cout << "    >>---- INITIAL CONFIG" << endl;
//    Eotq<int> node1(1);
//    Eotq<int> node2(2);
//    node1.dck=10; node1.plus(10);
//    node2.sck=20; node2.plus(20);
//    cout << node1 << endl;
//    cout << node2 << endl;
//    cout << "-------------------------< END >------------------------" << endl;
}

    

int main() {
    //test1();
    InitializeNodes();
    sleep(100);
}