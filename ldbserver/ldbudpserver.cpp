#include "ldbudpserver.h"

using namespace ldbserver;
using namespace ldbdata;

CLdbUdpServer::CLdbUdpServer()
{
}

CLdbUdpServer::~CLdbUdpServer()
{
}

int CLdbUdpServer::CreateServer(const char *ip, unsigned short usPort, int iBackLog)
{
    m_iSockFd = socket(AF_INET, SOCK_DGRAM, 0);
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

    return 0;
}

void CLdbUdpServer::StartLoop()
{
    ev::default_loop loop;

    m_io.set<CLdbUdpServer, &CLdbUdpServer::ProcessCallback>(this);
    m_io.start(m_iSockFd, ev::READ);

    loop.run(0);

    return;
}

void CLdbUdpServer::ProcessCallback(ev::io &wather, int revents)
{
    ProcessRequest();

    ProcessResponse();

    return;
}

void CLdbUdpServer::ProcessRequest()
{
    char buffer[BUF_SIZE] = {'\0'};

    int addr_len = sizeof(m_sockaddr);
    socklen_t bytes = recvfrom(m_iSockFd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*) &m_sockaddr, (socklen_t *) &addr_len);
    buffer[bytes] = 0;

    std::string sRequest(buffer);

    m_oRequest.ParseFromString(sRequest);
    SelectCommand(m_oRequest.cmd());

    return;
}

void CLdbUdpServer::ProcessResponse()
{
    int addr_len = sizeof(m_sockaddr);
    std::string sResonse;
    m_oResponse.SerializeToString(&sResonse);

    sendto(m_iSockFd, sResonse.c_str(), sResonse.size(), 0, (struct sockaddr*) &m_sockaddr, addr_len);

    return;
}

