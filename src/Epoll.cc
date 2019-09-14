#include <error.h>
#include <iostream>
#include <string.h>

#include "Epoll.hpp"
#include "Error.hpp"

#define EPOLL_TIMEOUT_LEN 5

int Epoll::initialize(int eventSize)
{
    m_eventSize = eventSize;
    m_epollFd = epoll_create(m_eventSize);
    mp_EpollEvents = new epoll_event[m_eventSize];
    memset(mp_EpollEvents, 0, sizeof(epoll_event) * m_eventSize);

    return SUCCESSFUL;
}

void Epoll::run()
{
    int nReady = 0;
    Agent* agent = NULL;

    while (1) {
        if ((nReady = epoll_wait(
                 m_epollFd, mp_EpollEvents, m_eventSize, EPOLL_TIMEOUT_LEN))
            < 0) {
            if (EINTR == errno) {
                continue;
            } else {
                std::cout << "Epoll:epoll_wait" << std::endl;
            }
        }

        for (int i = 0; i < nReady; i++) {
            agent = (Agent*)mp_EpollEvents[i].events;

            if (mp_EpollEvents[i].events & EPOLLOUT) {
            }
            if (mp_EpollEvents[i].events & EPOLLIN) {
            }
        }
    }
}
int Epoll::doAgent(int fd,
    unsigned int events,
    int op,
    Agent* agent)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(struct epoll_event));
    ev.events = events;
    ev.data.ptr = agent;
    if (epoll_ctl(m_epollFd, op, fd, &ev) < 0) {
        std::cout << "Epoll:doEvent epoll_ctl() error"
                  << strerror(errno) << std::endl;
        return FAILED;
    }
    return SUCCESSFUL;
}