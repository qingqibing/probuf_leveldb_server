/*
 * ldbudpserver.h
 */

#ifndef _LDB_UDP_SERVER_H_
#define _LDB_UDP_SERVER_H_

#include "ldbserver.h"

namespace ldbserver
{
    class CLdbUdpServer : public CLdbServer
    {
    public:
        CLdbUdpServer();
        CLdbUdpServer(const std::string& sFolder, const std::string& sDbName);
        ~CLdbUdpServer();
        int CreateServer(const char *ip, unsigned short usPort, int iBackLog=10);
        void StartLoop();

    private:
        void ProcessCallback(ev::io &wather, int revents);
        void ProcessRequest();
        void ProcessResponse();
    };
}

#endif

