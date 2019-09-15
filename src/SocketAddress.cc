#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "SocketAddress.hpp"

const size_t IPV4MAXLEN = 15;
const size_t MAXSOCKADDRLEN = 100;
const char* ANYADDR = "0";
const char* IPV4_ANYADDR = "0.0.0.0";

SocketAddress::SocketAddress()
    : m_strIp(IPV4_ANYADDR)
      , m_usPort(0){

}

SocketAddress::SocketAddress(const char* ip, unsigned short port){
    m_usPort = port;
    if (strlen(ip) > IPV4MAXLEN || strcmp(ip, ANYADDR) == 0) {
        m_strIp = IPV4_ANYADDR;
    } else {
        m_strIp = std::string(ip);
    }
}

SocketAddress::~SocketAddress(){

}

void SocketAddress::setPort(unsigned short port){
    m_usPort = port;    
}

void SocketAddress::setAddress(const char* ip, unsigned short port){
    m_usPort = port;
    if (strlen(ip) <= IPV4MAXLEN && strcmp(ip, ANYADDR) != 0) {
        m_strIp = std::string(ip);
    }
}

const char* SocketAddress::getIP(void){
    char ip[IPV4MAXLEN];
    memset(ip,0,sizeof(ip));
    return m_strIp.c_str();
}

sockaddr_in SocketAddress::getAddr(void){
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(m_strIp.c_str());
    addr.sin_port = htons(m_usPort);
    return addr;
}

bool SocketAddress::ifAnyAddr(void) const
{
    if (IPV4_ANYADDR == m_strIp) {
        return true;
    } else {
        return false;
    }
}

bool SocketAddress::operator==(const SocketAddress& h) const
{
    if (m_strIp == h.m_strIp && m_usPort == h.m_usPort) {
        return true;
    } else {
        return false;
    }
}

SocketAddress& SocketAddress::operator=(const SocketAddress& h)
{
    m_strIp = h.m_strIp;
    m_usPort= h.m_usPort;
    return *this;
}
