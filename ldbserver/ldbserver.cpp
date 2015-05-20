#include "ldbserver.h"

#include "OpenCommand.h"
#include "PutCommand.h"
#include "GetCommand.h"
#include "DeleteCommand.h"

using namespace ldbserver;
using namespace ldbdata;
using namespace std;

CLdbServer::CLdbServer()
{
}

CLdbServer::CLdbServer(const std::string& sFolder, const std::string& sDbName)
{
    m_iSockFd = -1;
    bzero(&m_sockaddr, sizeof(sockaddr));

    COpenCommand oOpenCmd;
    leveldb::DB* pLdb = oOpenCmd.GetLdbHandler(sFolder, sDbName);
    if (pLdb != NULL)
    {
        m_pPutCmd    = new CPutCommand(pLdb);
        m_pGetCmd    = new CGetCommand(pLdb);
        m_pDeleteCmd = new CDeleteCommand(pLdb);
    }
}

CLdbServer::~CLdbServer()
{
    if (m_iSockFd >= 0)
    {
        close(m_iSockFd);
        m_iSockFd = -1;
    }
    bzero(&m_sockaddr, sizeof(sockaddr));

    if (m_pPutCmd)
    {
        delete m_pPutCmd;
        m_pPutCmd = NULL;
    }

    if (m_pGetCmd)
    {
        delete m_pGetCmd;
        m_pGetCmd = NULL;
    }

    if (m_pDeleteCmd)
    {
        delete m_pDeleteCmd;
        m_pDeleteCmd = NULL;
    }
}

void CLdbServer::SelectCommand(uint32_t dwCmd)
{
    std::cout << "dwCmd=" << dwCmd  << std::endl;
    switch (dwCmd)
    {
        case PUT_CMD:
            ExecCommand(m_pPutCmd);
            break;

        case GET_CMD:
            ExecCommand(m_pGetCmd);
            break;

        case DELETE_CMD:
            ExecCommand(m_pDeleteCmd);
            break;

        default:
            break;
    }

    return;
}

void CLdbServer::ExecCommand(CCommand* pCmd)
{
    pCmd->SetRequestParam(m_oRequest);

    pCmd->execute();

    pCmd->SetResponseParam(m_oResponse);
}


