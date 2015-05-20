/*
 * ldbserver.h
 */

#ifndef _LDB_SERVER_H_
#define _LDB_SERVER_H_

#include <ev++.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "ldbdata.pb.h"
#include "Command.h"

#define BUF_SIZE (4096)

namespace ldbserver
{
    class CLdbServer
    {
    public:
        CLdbServer();
        CLdbServer(const std::string& sFolder, const std::string& sDbName);
        virtual ~CLdbServer();

        virtual int CreateServer(const char *ip, unsigned short usPort, int iBackLog=10)=0;
        virtual void StartLoop()=0;

    protected:
        virtual void ProcessCallback(ev::io &wather, int revents)=0;
        virtual void ProcessRequest()=0;
        virtual void ProcessResponse()=0;

        void SelectCommand(uint32_t dwCmd);
        void ExecCommand(CCommand* pCmd);

    protected:
        ev::io m_io;
        ldbdata::Request  m_oRequest;
        ldbdata::Response m_oResponse;

        int m_iSockFd;
        struct sockaddr_in m_sockaddr;

    private:
        //CCommand* m_pOenCmd;
        CCommand* m_pPutCmd;
        CCommand* m_pGetCmd;
        CCommand* m_pDeleteCmd;
    };
}

#endif

