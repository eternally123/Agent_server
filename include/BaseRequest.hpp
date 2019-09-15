#ifndef _BASEREQUEST_HPP_
#define _BASEREQUEST_HPP_

#include "MsgHeader.hpp"

class BaseRequset {
public:
    MsgHeader m_msgHeader;
    char* m_msgBody;
    sockaddr_in m_oppositeAddr;

    BaseRequset();
    ~BaseRequset();
};

#endif