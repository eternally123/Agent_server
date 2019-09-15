#ifndef _BASERESPONSE_HPP_
#define _BASERESPONSE_HPP_

#include "MsgHeader.hpp"

class BaseResponse {
public:
    MsgHeader m_msgHeader;
    char* m_msgBody;
    sockaddr_in m_oppositeAddr;

    BaseResponse();
    ~BaseResponse();
};

#endif