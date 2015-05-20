#include "ldbudpserver.h"

using namespace ldbserver;

#define LDB_PATH    ("/root")
#define LDB_FILE    ("test.ldb")

#define UDP_HOST ("127.0.0.1")
#define UDP_PORT (6789)

int main(int argc, char* argv[])
{
    std::cout << "Enter UdpServer...." << std::endl;

    CLdbUdpServer *pLdbserver = new CLdbUdpServer(LDB_PATH, LDB_FILE);
    if (NULL == pLdbserver)
    {
        return -1;
    }

    int iRet = pLdbserver->CreateServer(UDP_HOST, UDP_PORT);
    if (iRet != 0)
    {
        std::cerr << "CreateUdpServer fail" << std::endl;
        return -1;
    }

    pLdbserver->StartLoop();

    // This point is never reached.
    if (NULL != pLdbserver)
    {
        delete pLdbserver;
        pLdbserver = NULL;
    }

    std::cout << "Exit from UdpServer...." << std::endl;
    return 0;
}

