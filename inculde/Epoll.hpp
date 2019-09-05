#ifndef _EPOLL_HPP_
#define _EPOLL_HPP_

#include <sys/epoll.h>

class Epoll{
public:
    int m_epollFd;
    int m_eventSize;
    struct epoll_event* mp_EpollEvents;

public:
    Epoll() {}
    ~Epoll() {}

    int initialize(int eventSize);
    void addEvent(int fd,struct epoll_event* event);
    void modEvent(int fd,struct epoll_event* event);
    void deleteEvent(int fd,struct epoll_event* event);
    void run();
};

#endif




