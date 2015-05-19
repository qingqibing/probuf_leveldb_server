#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include "test_udp_client.h"

#define UDP_HOST ("127.0.0.1")
#define UDP_PORT (6789)

using namespace ldbdata;

CTestUdpClient::CTestUdpClient()
{
    m_iSockFd = -1;
    bzero(&m_sockaddr, sizeof(sockaddr));
}

CTestUdpClient::~CTestUdpClient()
{
    if (m_iSockFd >= 0)
    {
        close(m_iSockFd);
        m_iSockFd = -1;
    }
    bzero(&m_sockaddr, sizeof(sockaddr));
}

int CTestUdpClient::new_udp_client(const char *ip, unsigned short usPort)
{
    m_iSockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_iSockFd < 0)
    {
        return errno;
    }

    m_sockaddr.sin_family      = AF_INET;
    m_sockaddr.sin_addr.s_addr = inet_addr(ip);
    m_sockaddr.sin_port        = htons(usPort);

    return 0;
}

void  CTestUdpClient::TestProcessRequest(const std::string& sRequest)
{
    int addr_len = sizeof(m_sockaddr);
    sendto(m_iSockFd, sRequest.c_str(), sRequest.size(), 0, (struct sockaddr*) &m_sockaddr, addr_len);

    char buffer[4096] = {'\0'};
    socklen_t bytes = recvfrom(m_iSockFd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*) &m_sockaddr, (socklen_t *) &addr_len);
    buffer[bytes] = '\0';
    std::string sResponse(buffer);
    m_oResponse.Clear();
    m_oResponse.ParseFromString(sResponse);

    std::cout << "retcode=" << m_oResponse.retcode()            << std::endl;
    std::cout << "value=" << m_oResponse.value()       << std::endl     << std::endl;
}

int main()
{
    CTestUdpClient  oUdpClient;
    oUdpClient.new_udp_client(UDP_HOST, UDP_PORT);

    ldbdata::Request  oRequest;
    std::string sRequest;

    // Test Get
    std::cout << "Begin to test get..." << std::endl;
    oRequest.set_cmd(Request_Cmd_GET);
    oRequest.set_key("test321");
    oRequest.SerializeToString(&sRequest);
    oUdpClient.TestProcessRequest(sRequest);


    // Test Put
    std::cout << "Begin to test put..." << std::endl;
    sRequest="";
    oRequest.Clear();
    oRequest.set_cmd(Request_Cmd_PUT);
    oRequest.set_key("test321");
    oRequest.set_value("1234567");
    oRequest.SerializeToString(&sRequest);
    oUdpClient.TestProcessRequest(sRequest);

    // Test Get
    std::cout << "Begin to test get..." << std::endl;
    sRequest="";
    oRequest.Clear();
    oRequest.set_cmd(Request_Cmd_GET);
    oRequest.set_key("test321");
    oRequest.SerializeToString(&sRequest);
    oUdpClient.TestProcessRequest(sRequest);

    // Test Delete
    std::cout << "Begin to test delete..." << std::endl;
    sRequest="";
    oRequest.Clear();
    oRequest.set_cmd(Request_Cmd_DELETE);
    oRequest.set_key("test321");
    oRequest.SerializeToString(&sRequest);
    oUdpClient.TestProcessRequest(sRequest);

    // Test Get
    std::cout << "Begin to test get..." << std::endl;
    sRequest="";
    oRequest.Clear();
    oRequest.set_cmd(Request_Cmd_GET);
    oRequest.set_key("test321");
    oRequest.SerializeToString(&sRequest);
    oUdpClient.TestProcessRequest(sRequest);

    return 0;
}
