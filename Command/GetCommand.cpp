#include "GetCommand.h"

CGetCommand::CGetCommand()
{
}

CGetCommand::CGetCommand(leveldb::DB* pLdb)
{
    m_pLdb = pLdb;
}

CGetCommand::~CGetCommand()
{
}

void CGetCommand::execute()
{
    m_oResponse.Clear();

    std::string sKey, sValue;
    if (m_oRequest.has_key())
    {
        sKey = m_oRequest.key();
    }
    else
    {
        m_oResponse.set_retcode(LDB_SERVER_KEY_IS_NULL);
        return;
    }

    m_status = m_pLdb->Get(leveldb::ReadOptions(), sKey, &sValue);
    if (!m_status.ok())
    {
        m_oResponse.set_retcode(LDB_SERVER_GET_FAIL);
    }
    else
    {
        m_oResponse.set_retcode(LDB_SERVER_SUCCESS);
        m_oResponse.set_value(sValue);
    }

    return;
}


