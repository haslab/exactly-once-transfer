#include <cstdlib>
#include <map>
#include <iostream>
#include <string>
#include <unistd.h>
#include "Message.h"
#include "UDPSocket.h"
#include <vector>
#include <boost/algorithm/string/trim.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

#define START_LST_PORT  8000    // 1st port to start listen
#define NUM_NODES       4       // # of nodes to spawn

float zero() {
    return 0;
}

float oplus(const float &a, const float &b) {
    return a + b;
}

int oplus(const int &a, const int &b) {
    return a + b;
}

float needs(const float &a, const float &b) {
    return (b - a + abs(b - a)) / 4;
}

int needs(const int &a, const int &b) {
    return (b - a + abs(b - a)) / 4;
}

pair<float, float> split(const float & x, const float & h) {
    pair<float, float> r;
    r.first = (x - h + abs(x - h)) / 2;
    r.second = (x + h - abs(x - h)) / 2;
    return r;
}

pair<int, int> split(const int & x, const int & h) {
    pair<int, int> r;
    r.first = (x - h + abs(x - h)) / 2;
    r.second = (x + h - abs(x - h)) / 2;
    return r;
}

template<typename T>
class Eotq {
private:  
public:
    T val;
    int id;
    int sck;
    int dck;
    int port;
    
    map < int, pair<pair<int, int>, T> > slots;
    map < int, pair<pair<int, int>, T> > tokens;
    
    map < int, pair<string, int> > neighbors;
    
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
    void plus(T v) {
        val = oplus(val, v);
    }
    
    unsigned int numTokens() {
        return tokens.size();
    }

    unsigned int numSlots() {
        return slots.size();
    }

    /* parse the node content to screen */
    friend ostream &operator<<(ostream &output, const Eotq &o) {
        output << "id: " << o.id << " val: " << o.val <<
                  " sck: " << o.sck << " dck: " << o.dck << endl;
        typename map < int, pair<pair<int, int>, T> >::const_iterator it;
        typename map < int, pair<string, int> >::const_iterator ne;
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
        
//        for (ne = o.neighbors.begin(); ne != o.neighbors.end(); ne++) {
//            output << "NEIGHBOR: ( " << ne->first
//                   << ", [ip_addr:" << ne->second.first << ", port: " << ne->second.second << "], "
//                   << ")"<< endl;
//        }
        
        return output;
    }
    void fillSlots(Eotq<T> &j) {
        cout << "fillSlots" << endl;
        typename map<int, pair<pair<int, int>, T > >::iterator its = slots.find(j.id);
        typename map<int, pair<pair<int, int>, T > >::iterator itt;
        pair<pair<int, int>, T> token;
        pair<pair<int, int>, T> slot;

        if ( its != slots.end() ) {
            // j \in dom(slots_i)
            slot = its->second;
            itt = j.tokens.begin();
            if ( itt != j.tokens.end() ) {
                token = itt->second;
                if ( token.first == slot.first ) {
                    val = oplus(val, token.second);
                    slots.erase(its);
                } 
                else if ( itt->second.first.first > its->second.first.first )
                    slots.erase(its);
            }
        }
        //else:
        //there's no corresponding slot_i for this token
        //token to be removed in GCTokens
        //need to check up on this later
    }
    
    bool createSlot(Eotq<T> &j) {
        cout << "CreateSlot" << endl;
        typename map < int, pair<pair<int, int>, T> >::iterator its = slots.find(j.id);

        if ( its == slots.end() ) {
            T hint;
            hint = needs(val, j.val);
            //cout << "VAL_1=" << val << " :: VAL_2=" << j.val << " :: H=" << hint << endl;
            if ( hint != zero() ) {
                slots[j.id] = make_pair(make_pair(j.sck, dck), hint);
                dck++;
                return 1;
            }
        }
        //else cout << "SLOT[" << j.id << "] already exists !!!" << endl;
        return 0;
    }
    
    void GCTokens(Eotq<T> &j) {
        cout << "GCTokens" << endl;
        typename map<int, pair<pair<int, int>, T > >::iterator its;
        typename map<int, pair<pair<int, int>, T > >::iterator itt = tokens.find(j.id);
        pair<pair<int, int>, T> token;
        pair<pair<int, int>, T> slot;
        
        if ( itt != tokens.end() ) {
            // j \in dom(i.tokens)
            token = itt->second;
            its = j.slots.begin();
            if ( its != j.slots.end() ) {
                // i \in dom(j.slots)
                slot = its->second;
                if ( token.first.second < slot.first.second ) {
                    tokens.erase(itt);
                }
            } 
            else {
                // i \not \in dom(j.slots)
                if ( token.first.second < j.dck )
                    tokens.erase(itt);
            }
        }
    }
    
    bool createToken(Eotq<T> &j) {
        cout << "CreateToken" << endl;
        typename map<int, pair<pair<int, int>, T > >::iterator its = j.slots.begin();
        pair<pair<int, int>, T> token;
        pair<pair<int, int>, T> slot;
        
        if ( its != j.slots.end() ) {
            // i \in dom(j.slots)
            slot = its->second;
            if ( slot.first.first == sck ) {
                pair<T, T> p = split(val, slot.second);
                val = p.first;
                token.first = slot.first;
                token.second = p.second;
                tokens[j.id] = token;
                sck++;
                return 1;
            }
        }
        return 0;
    }
    
    void startListening()  {
        UDPSocket udp;
        Message *msg_rcv;
        if ( udp.createSocket() ) {
            //cout << "[SUCCESS]: Creating socket." << endl;
            if ( udp.bindSocket("", port) ) {
                cout << "[SUCCESS]: Binded on port " << port << endl;
                for (;;) {
                    //cout << "Waiting new message." << endl;
                    if ( (msg_rcv = udp.listenMessage()) != NULL ) {
                        cout << ">------------------------[ " << id << ": RECEPTION ]------------------------------<" <<endl; 
                        cout << "RAW_MSG_RECV: [" << msg_rcv->getByteSize() << "] bytes" << endl << msg_rcv->getRaw();
                        
                        stringstream sstream(msg_rcv->getNodeVal());
                        Eotq<T> r_node(msg_rcv->getNodeId());
                        bool send_reply = 0;
                        
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
                        
                        if ( msg_rcv->hasToken() )
                            fillSlots(r_node);
                        send_reply = createSlot(r_node) ? 1 : 0;
                        GCTokens(r_node);
                        if ( msg_rcv->hasSlot() )
                            send_reply = createToken(r_node) || send_reply ? 1 : 0;
                        
                        if ( send_reply ) {
                            cout << ">------------------------[ " << id << ": REPLYING ]------------------------------<" <<endl; 

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

                            cout << "RAW_MSG_REPLY: [" << msg_reply.getByteSize() << "] bytes" << endl << msg_reply.getRaw();
                            UDPSocket udp_send;
                            if (udp_send.createSocket()) {
                                if (udp_send.bindSocket("", 0)) {
                                    udp_send.sendMessage(msg_reply, msg_rcv->getSenderAddr(), neighbors[r_node.id].second);
                                    udp_send.closeSocket();
                                }
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
    void prepareToSpam() {
        typename map < int, pair<string, int> >::const_iterator itn;

        for (;;) {
            int sleepTime = (rand() % 30) + 1;
            boost::this_thread::sleep_for(boost::chrono::seconds(sleepTime));
            for (itn = neighbors.begin(); itn != neighbors.end(); itn++) {
                boost::thread th(boost::bind(&Eotq<T>::startSpam, this, itn));
                th.detach();
            }
        }
    }
    
    void startSpam(typename map < int, pair<string, int> >::const_iterator &itn) {
        //cout << "FROM: " << id << ":" << port << " :: val=" << val << endl;
        //cout << "TO: " << itn->first << ":" << itn->second.second << endl;
        UDPSocket udp;
        
        if ( udp.createSocket() ) 
        {
            if ( udp.bindSocket("", 0) ) 
            {
                typename map < int, pair<pair<int, int>, T> >::iterator its = slots.find(itn->first);
                typename map < int, pair<pair<int, int>, T> >::iterator itt = tokens.find(itn->first);

                Message msg;
                msg.setNodeId(id);
                msg.setNodeSck(sck);
                msg.setNodeDck(dck);
                stringstream sstream;
                sstream << val;
                msg.setNodeVal(sstream.str());
                if ( its != slots.end() ) {
                    sstream.str(std::string());
                    sstream.clear();
                    sstream << its->second.second;
                    msg.setNodeSlot(its->second.first.first, its->second.first.second, sstream.str());
                }
                if ( itt != tokens.end() ) {
                    sstream.str(std::string());
                    sstream.clear();
                    sstream << itt->second.second;
                    msg.setNodeToken(itt->second.first.first, itt->second.first.second, sstream.str());
                }
                
                cout << ">------------------------[ " << id << ": SPAMMING ]------------------------------<" <<endl; 
                cout << "Sending from: " << id << "->" << itn->first << " -- [" << itn->second.first << ":" << itn->second.second << "]"<< endl << msg.getRaw();
                udp.sendMessage(msg, udp.convertIP((string &)itn->second.first), itn->second.second);
                udp.closeSocket();
            } 
            else {
                cout << "[ERROR]: Trying to bind. [void startSpam(...)]" << endl;
            }
        }
        else {
            cout << "[ERROR]: Trying to create socket. [void startSpam(...)]" << endl;
        }
    }
    
    void testThread() {
        for (;;) {
            cout << id << ":" << port << " -> " << val << endl;
            sleep(2);
        }
    }
};

/* Starting with global declarations */
vector< Eotq<int> > nodes(NUM_NODES);

vector<string> splitOptString(const string &s, char delim) 
{
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
                    else if ( ops[0] == "done" )
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
    /* Initialize base values values to nodes (if needed) */
    for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
        nodes[i].id     = i;
        nodes[i].port   = START_LST_PORT + i;
        nodes[i].val    = 20*i;
        
        /* Initialization for testing */
//        nodes[i].val = 4;
//        nodes[i].sck = 10;
//        nodes[i].dck = 100;
        /* END Initialization */
        
    }
    
    for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
        for(vector<int>::size_type j = 0; j != nodes.size(); j++) {
            if ( i != j ) {
                nodes[i].neighbors[j].first  = "127.0.0.1";
                nodes[i].neighbors[j].second = nodes[j].port;

                /* Initialization for testing */
                //nodes[i].neighbors[j].second = 7500;
                /* END Initialization */
            }
        }
    }
    
    //nodes[0].annouceResourcesToNeighbor("127.0.0.1", 8888);
    
    /* Create initial socket for listening*/    
    for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
        //boost::thread nodeListen(boost::bind(&Eotq<int>::testThread, &nodes[i]));
        boost::thread thl(boost::bind(&Eotq<int>::startListening, &nodes[i]));
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
    for(vector<int>::size_type i = 0; i != nodes.size(); i++) {
        boost::thread ths(boost::bind(&Eotq<int>::prepareToSpam, &nodes[i]));
    }
    
    
    /* Broker thread */
    boost::thread broker(boost::bind(brokerThread, "", 7000));
    broker.detach();
    //cout << "Waiting for clients to join." << endl;
    //broker.join();
    //cout << "Terminating broker thread." << endl;
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
    sleep(200);
}