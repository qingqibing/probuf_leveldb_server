#include "PutCommand.h"

CPutCommand::CPutCommand()
{
}

CPutCommand::CPutCommand(leveldb::DB* pLdb)
{
    m_pLdb = pLdb;
}

CPutCommand::~CPutCommand()
{
}

void CPutCommand::execute()
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

    if (m_oRequest.has_value())
    {
        sValue = m_oRequest.value();
    }
    else
    {
        m_oResponse.set_retcode(LDB_SERVER_VALUE_IS_NULL);
        return;
    }

    leveldb::WriteOptions write_options;
    write_options.sync = false;

    m_status = m_pLdb->Put(write_options, sKey, sValue);
    if (!m_status.ok())
    {
        m_oResponse.set_retcode(LDB_SERVER_PUT_FAIL);
    }
    else
    {
        m_oResponse.set_retcode(LDB_SERVER_SUCCESS);
    }

    return;
}


