#ifndef _MSGHEADER_HPP_
#define _MSGHEADER_HPP_

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

#endif