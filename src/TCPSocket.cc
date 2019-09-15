#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include <iostream>

#include "Error.hpp"
#include "SocketAddress.hpp"
#include "TCPSocket.hpp"

TCPSocket::TCPSocket()
    : m_iSockFd(-1)
{
}

TCPSocket::TCPSocket(int fd)
    : m_iSockFd(fd)
{
}

TCPSocket::~TCPSocket()
{
}

int TCPSocket::generateSocket(void)
{
    m_iSockFd= socket(PF_INET, SOCK_STREAM, 0);
    if (m_iSockFd< 0) {
        std::cout << "TCPSocket::TCPSocket::socket" << std::endl;
    }

    return m_iSockFd;
}

int TCPSocket::bind(const SocketAddress& servaddr)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = PF_INET;

    if (servaddr.ifAnyAddr()) {
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        if ((inet_aton(servaddr.getIP(), (in_addr*)&addr.sin_addr.s_addr)) == 0) {
            std::cout << "TCPSocket::bind::inet_addr: IP Address Invalid "
                      << std::endl;
            return FAILED;
        }
    }

    if (servaddr.getPort() == 0) {
        std::cout << "TCPSocket::bind: Port Invalid" << std::endl;
        return FAILED;
    }

    addr.sin_port = htons(servaddr.getPort());
    if (::bind(m_iSockFd, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cout << "TCPSocket::bind : bind error, Port is" << servaddr.getPort()
                  << "." << std::endl;
        return FAILED;
    }

    return SUCCESSFUL;
}

int TCPSocket::listen(int len)
{
    if (::listen(m_iSockFd, len) < 0) {
        std::cout << "TCPSocket::listen::listen" << std::endl;
        return FAILED;
    }

    return SUCCESSFUL;
}

int TCPSocket::connect(const SocketAddress& ipaddr)
{
    int ret = -1;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = PF_INET;
    if (ipaddr.ifAnyAddr()) {
        std::cout << "TCPSocket::connect:ipaddr.ip NULL" << std::endl;
        return FAILED;
    } else {
        if ((addr.sin_addr.s_addr = inet_addr(ipaddr.getIP())) == INADDR_NONE) {
            std::cout << "TCPSocket::connect::inet_addr: IP Address Invalid" << std::endl;
            return FAILED;
        }
    }
    if (ipaddr.getPort() == 0) {
        std::cout << "TCPSocket::connect:ipaddr.Port Invalid" << std::endl;
        return FAILED;
    }
    addr.sin_port = htons(ipaddr.getPort());

    ret = ::connect(m_iSockFd, (struct sockaddr*)&addr, sizeof(addr));
    return ret;
}

int TCPSocket::accept(SocketAddress& addr)
{
    struct sockaddr_in cliAddr;
    unsigned int cliAddrLen = sizeof(cliAddr);
    memset(&cliAddr, 0, cliAddrLen);
    int fd = ::accept(m_iSockFd, (struct sockaddr*)&cliAddr, &cliAddrLen);
    addr.setAddress(inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));
    return fd;
}

int TCPSocket::close(void)
{
    if (m_iSockFd== -1) {
        return SUCCESSFUL;
    }
    if (::close(m_iSockFd) < 0) {
        std::cout << "TCPSocket::close::close" << std::endl;
        return FAILED;
    }
    m_iSockFd = -1;

    return SUCCESSFUL;
}

int TCPSocket::getFd(void) const
{
    return m_iSockFd;
}

int TCPSocket::read(char* buf, size_t len)
{
    int readNum = ::read(m_iSockFd, buf, len);
    return readNum;
}

int TCPSocket::readn(char* vptr, unsigned int n)
{
    unsigned int nleft;
    int nread;
    char* ptr;

    if (!vptr) {
        return FAILED;
    }
    ptr = vptr;
    nleft = n;

    while (nleft > 0) {
        if ((nread = ::read(m_iSockFd, ptr, nleft)) < 0) {
            if (errno == EINTR) {
                nread = 0;
            } else if (errno != EWOULDBLOCK) {
                std::cout << "readn():" << std::endl;
                return FAILED;
            }
        } else if (nread == 0) {
            break;
        } else {
            nleft -= (unsigned int)nread;
            ptr += nread;
        }
    }

    return (int)(n - nleft);
}

int TCPSocket::write(const char* buf, size_t len)
{
    int writeNum = ::write(m_iSockFd, buf, len);
    return writeNum;
}

int TCPSocket::writev(const struct iovec* v, size_t c)
{
    int writeNum = ::writev(m_iSockFd, v, c);
    return writeNum;
}

int TCPSocket::setNonblock(void)
{
    int val;

    if ((val = fcntl(m_iSockFd, F_GETFL, 0)) < 0) {
        std::cout << "TCPSocket::setNonBlock::fcntl-F_GETFL" << std::endl;
        return val;
    }
    val |= O_NONBLOCK;
    if (fcntl(m_iSockFd, F_SETFL, val) < 0) {
        std::cout << "TCPSocket::setNonBlock:fcntl" << std::endl;
        return FAILED;
    }

    return SUCCESSFUL;
}

