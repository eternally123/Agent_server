#ifndef _SOCKETADDRESS_H_
#define _SOCKETADDRESS_H_

#include <netinet/in.h>
#include <string>

class SocketAddress {
private:
    std::string m_strIp;
    unsigned short m_usPort;

public:
    SocketAddress(); 
    SocketAddress(const char* ip, unsigned short port); 
    ~SocketAddress();

    void setPort(unsigned short);
    void setAddress(const char* ip, unsigned short port);
    const char* getIP(void);
    unsigned short getPort(void);
    sockaddr_in getAddr(void);

    bool ifAnyAddr(void) const; //for ip

    bool operator==(const SocketAddress&) const;
    SocketAddress& operator=(const SocketAddress&);
};

#endif
