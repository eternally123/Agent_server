#ifndef _EPOLL_HPP_
#define _EPOLL_HPP_
#include <sys/epoll.h>

#include "TCPAgent.hpp"

class Epoll {
private:
    int m_epollFd;
    int m_eventSize;
    struct epoll_event* mp_EpollEvents;

public:
    Epoll() {}
    ~Epoll() {}

    int initialize(int eventSize);
    void run();

protected:
    int doAgent(int fd, unsigned int events, int op, Agent* agent);
};

#endif
