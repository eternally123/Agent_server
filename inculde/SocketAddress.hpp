#ifndef _SOCKETADDRESS_H_
#define _SOCKETADDRESS_H_

#include <netinet/in.h>
#include <string>

using namespace std;

class SocketAddress {
    /*
        getAddr
        operator=

        ip 地址
     */
private:
    string m_ip;
    unsigned short m_port;
    string m_str;

public:
    SocketAddress();
    SocketAddress(const char* ip, unsigned short port);
    ~SocketAddress();

    void setPort(unsigned short);
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
    bool getAddr(sockaddr_in& addr);

    string& convertToString(void);
    bool ifAnyAddr(void) const;

    bool operator==(const SocketAddress&) const;
    SocketAddress& operator=(const SocketAddress&);
};

#endif
