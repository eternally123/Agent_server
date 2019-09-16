#ifndef _MSGHEADER_HPP_
#define _MSGHEADER_HPP_

#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>

class MsgHeader {
public:
    uint32_t m_u32MsgBodyLength;
    uint32_t m_u32OppoId;

    MsgHeader();
    ~MsgHeader();
};

#endif
