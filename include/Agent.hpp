#ifndef _AGENT_HPP_
#define _AGENT_HPP_

#include <stdint.h>

#include "Error.hpp"

struct BaseRequest;
struct InReq;
class SocketAddress;

class Agent {
public:
    Agent();
    virtual ~Agent();

    virtual int recvData(void);
    virtual int sendData(void);
    virtual int recvReq(BaseRequest* req);
    virtual void writeBack(bool result);
    virtual void readBack(InReq& req);

    virtual int connectAfter(bool);
    virtual int connect(const SocketAddress&);
    virtual int connect();

    virtual int getOppAddr(SocketAddress&);
    virtual int getErrno();
    int getConnectTimes() const;

protected:
};
#endif
