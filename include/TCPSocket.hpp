#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include <sys/types.h>

class SocketAddress;

class TCPSocket {
public:
    TCPSocket();
    TCPSocket(int fd);
    ~TCPSocket();

    int generateSocket(void);
    int bind(const SocketAddress& serverAddr);
    int listen(int len);
    int connect(const SocketAddress& serverAddr);
    int accept(SocketAddress& serverAddr);
    int close(void);

    int getFd(void) const;
    int read(char* buf, size_t len);
    int readn(char* buf, unsigned int n);
    int write(const char* buf, size_t len);
    int writev(const struct iovec*, size_t);

    int setNonblock(void);

private:
    int m_iSockFd;
};

#endif
