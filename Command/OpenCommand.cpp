#include "OpenCommand.h"

COpenCommand::COpenCommand()
{
}

COpenCommand::~COpenCommand()
{
}

void COpenCommand::execute()
{
}

leveldb::DB* COpenCommand::GetLdbHandler(const std::string& sFolder, const std::string& sDbName)
{
    leveldb::DB* pLdb = NULL;
    leveldb::Options options;
    options.create_if_missing = true;

    m_status = leveldb::DB::Open(options, sFolder + "/" + sDbName, &pLdb);
    if (!m_status.ok())
    {
        std::cerr << m_status.ToString() << std::endl;
        return NULL;
    }

    return pLdb;
}


