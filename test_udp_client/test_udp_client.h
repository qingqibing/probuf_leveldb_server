#ifndef _TEST_UDP_CLIENT_H_
#define _TEST_UDP_CLIENT_H_

#include "ldbdata.pb.h"

class CTestUdpClient
{
public:
    CTestUdpClient();
    ~CTestUdpClient();

    int new_udp_client(const char *ip, unsigned short usPort);
    void TestProcessRequest(const std::string& sRequest);


private:
    ldbdata::Request  m_oRequest;
    ldbdata::Response m_oResponse;

    int m_iSockFd;
    struct sockaddr_in m_sockaddr;
};

#endif
