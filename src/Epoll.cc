#include <string.h>

#include "Epoll.hpp"
#include "error.hpp"

int Epoll::initialize(int eventSize){
    m_eventSize = eventSize;
    m_epollFd = epoll_create(m_eventSize);
    mp_EpollEvents = new epoll_event[m_eventSize];
    memset(mp_EpollEvents,0,sizeof(epoll_event)*m_eventSize);
    
    return SUCCESSFUL;
}

void Epoll::addEvent(int fd,struct epoll_event* event){
    epoll_ctl(m_epollFd,)
}

