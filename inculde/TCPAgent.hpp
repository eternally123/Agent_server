#ifndef TCPAGENT_H_
#define TCPAGENT_H_

#include "Agent.hpp"
#include "SocketAddress.hpp"
#include "TCPSocket.hpp"

const SocketAddress InitAddr("0", 0);

struct InReq;

class TCPAgent : public Agent {
public:
    TCPAgent();
    TCPAgent(const SocketAddress&);
    TCPAgent(const TCPSocket&, const SocketAddress&);
    virtual ~TCPAgent();

    int connect();
    virtual int init();
    virtual int sendData(void);
    virtual int recvData(void);
    virtual int doParse(void);
    virtual int doPackage(void);

    virtual void readBack(InReq&) {}
    virtual void writeBack(bool) {}
    virtual int connectAfter(bool);

    int writeToBuffer(char* buf, unsigned int len);

    virtual int getOppAddr(SocketAddress& sockAddr);

    void setState(int st);
    int getErrno();

    TCPSocket getSocket() const;

protected:
    TCPSocket m_socket;
};
#endif
