#include "DeleteCommand.h"

CDeleteCommand::CDeleteCommand()
{
}

CDeleteCommand::CDeleteCommand(leveldb::DB* pLdb)
{
    m_pLdb = pLdb;
}

CDeleteCommand::~CDeleteCommand()
{
}

void CDeleteCommand::execute()
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

    bool bSynFlag = false;
    if (m_oRequest.has_synflag())
    {
        bSynFlag = m_oRequest.synflag();
    }

    leveldb::WriteOptions write_options;
    write_options.sync = bSynFlag;
    m_status = m_pLdb->Delete(write_options, sKey);
    if (!m_status.ok())
    {
        m_oResponse.set_retcode(LDB_SERVER_DELETE_FAIL);
    }
    else
    {
        m_oResponse.set_retcode(LDB_SERVER_SUCCESS);
    }

    return;
}


