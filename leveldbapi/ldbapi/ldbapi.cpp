#include "ldbapi.h"

using namespace ldbapi;

CLevelDb::CLevelDb()
{
    m_pLdb  = NULL;
}

CLevelDb::~CLevelDb()
{
    if (m_pLdb)
    {
        delete m_pLdb;
        m_pLdb = NULL;
    }
}

bool CLevelDb::Open(const std::string& sFolder, const std::string& sDbName)
{
    leveldb::Options options;
    options.create_if_missing = true;
    //options.error_if_exists   = true;

    m_status = leveldb::DB::Open(options, sFolder + "/" + sDbName, &m_pLdb);
    if (!m_status.ok())
    {
        std::cerr << "Unable to create database, " << m_status.ToString() << std::endl;
    }

    return m_status.ok();
}

bool CLevelDb::Put(const std::string& sKey, const std::string& sValue, bool bSyncFlag)
{
    leveldb::WriteOptions write_options;
    write_options.sync = bSyncFlag;

    m_status = m_pLdb->Put(write_options, sKey, sValue);
    if (!m_status.ok())
    {
        std::cerr << m_status.ToString() << std::endl;
    }

    return m_status.ok();
}

bool CLevelDb::Get(const std::string& sKey, std::string& sValue)
{
    m_status = m_pLdb->Get(leveldb::ReadOptions(), sKey, &sValue);
    if (!m_status.ok())
    {
        std::cerr << m_status.ToString() << std::endl;
    }

    return m_status.ok();
}

bool CLevelDb::MultiGet(const std::string& sKey, std::string& sValue)
{
    leveldb::Iterator* it = m_pLdb->NewIterator(leveldb::ReadOptions());
    it->Seek(sKey);
    if (!it->Valid())
    {
        delete it;
        return false;
    }

    while (it->Valid() && it->key().ToString() == sKey)
    {
        sValue = it->value().ToString() + ":";
        it->Next();
    }
    delete it;

    return true;
}

bool CLevelDb::Delete(const std::string& sKey, bool bSyncFlag)
{
    leveldb::WriteOptions write_options;
    write_options.sync = bSyncFlag;

    m_status = m_pLdb->Delete(write_options, sKey);
    if (!m_status.ok())
    {
        std::cerr << m_status.ToString() << std::endl;
    }

    return m_status.ok();
}

bool CLevelDb::WriteBatch(leveldb::WriteBatch& batch, bool bSyncFlag)
{
    leveldb::WriteOptions write_options;
    write_options.sync = bSyncFlag;

    m_status = m_pLdb->Write(write_options, &batch);
    if (!m_status.ok())
    {
        std::cerr << m_status.ToString() << std::endl;
    }

    return m_status.ok();
}


