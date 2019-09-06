#ifndef _BASEREQUEST_HPP_
#define _BASEREQUEST_HPP_

#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>

class MsgHeader {
public:
    uint32_t m_cmd;
    uint32_t m_msgBodyLength;
    uint32_t m_error;
    uint32_t m_para1;
    uint32_t m_para2;

    MsgHeader();
    ~MsgHeader();
};

class BaseRequset {
public:
    MsgHeader m_msgHeader;
    char* m_msgBody;
    sockaddr_in m_oppositeAddr;

    BaseRequset();
    ~BaseRequset();
};

#endif