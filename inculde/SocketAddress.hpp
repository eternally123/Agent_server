#ifndef _SOCKETADDRESS_H_
#define _SOCKETADDRESS_H_

#include <netinet/in.h>
#include <string>

using namespace std;

class SocketAddress {
private:
    string m_ip;
    unsigned short m_port;
    string m_str;

public:
    SocketAddress(); //for local
    SocketAddress(const char* ip, unsigned short port); //for remote
    ~SocketAddress();

    void setPort(unsigned short); //for server bind
    void setAddress(const char* ip, unsigned short port);
    const char* getIP(void) const
    {
        return m_ip.c_str();
    };
    unsigned short getPort(void) const
    {
        return m_port;
    };
    sockaddr_in getAddr(void);

    string& convertToString(void);
    bool ifAnyAddr(void) const; //for ip

    bool operator==(const SocketAddress&) const;
    SocketAddress& operator=(const SocketAddress&);
};

#endif
