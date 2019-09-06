

#include "BaseRequest.hpp"

MsgHeader::MsgHeader()
    : m_cmd(0)
    , m_msgBodyLength(0)
    , m_error(0)
    , m_para1(0)
    , m_para2(0)
{
}

MsgHeader::~MsgHeader()
{
}

BaseRequset::BaseRequset()
{
}

BaseRequset::~BaseRequset()
{
}