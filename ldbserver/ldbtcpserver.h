/*
 * ldbtcpserver.h
 */

#ifndef _LDB_TCP_SERVER_H_
#define _LDB_TCP_SERVER_H_

#include "ldbserver.h"

namespace ldbserver
{
    class CLdbTcpServer : public CLdbServer
    {
    public:
        CLdbTcpServer();
        ~CLdbTcpServer();
        int CreateServer(const char *ip, unsigned short usPort, int iBackLog=10);
        void StartLoop();

    private:
        void ProcessCallback(ev::io &wather, int revents);
        void ProcessRequest();
        void ProcessResponse();
    };
}

#endif

