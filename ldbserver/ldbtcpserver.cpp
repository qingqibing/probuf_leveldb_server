#include "ldbtcpserver.h"

using namespace ldbserver;
using namespace ldbdata;

CLdbTcpServer::CLdbTcpServer()
{
}

CLdbTcpServer::~CLdbTcpServer()
{
}

int CLdbTcpServer::CreateServer(const char *ip, unsigned short usPort, int iBackLog)
{
    m_iSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_iSockFd < 0)
    {
        return errno;
    }

    m_sockaddr.sin_family      = AF_INET;
    m_sockaddr.sin_addr.s_addr = inet_addr(ip);
    m_sockaddr.sin_port        = htons(usPort);

    int iRet = 0;
    iRet = bind(m_iSockFd, (struct sockaddr *)&m_sockaddr, sizeof(sockaddr));
    if (iRet < 0)
    {
        close(m_iSockFd);
        m_iSockFd = -1;
        return errno;
    }

    iRet = listen(m_iSockFd, iBackLog);
    if (iRet < 0)
    {
        close(m_iSockFd);
        m_iSockFd = -1;
        return errno;
    }

    return 0;
}

void CLdbTcpServer::ProcessCallback(ev::io &wather, int revents)
{
    ProcessRequest();

    ProcessResponse();

    return;
}

void CLdbTcpServer::ProcessRequest()
{
    return;
}

void CLdbTcpServer::ProcessResponse()
{
    return;
}

