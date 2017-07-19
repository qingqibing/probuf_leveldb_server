/**
    * @file   : ldbapi.h
    * @brief
    *
    * 针对leveldb做了一层面向对象的封装，以便于在C++程序中使用
    *
    * @author  :  youzp
    * @version :  0.1
    * @date    :  2015/04/30
*/

#ifndef _LDBAPI_H_
#define _LDBAPI_H_

#include <iostream>
#include <leveldb/db.h>
#include <leveldb/status.h>
#include <leveldb/write_batch.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

namespace ldbapi
{
    class CLevelDb
    {
    public:
        CLevelDb();
        virtual ~CLevelDb();

        /* open/create the database */
        bool Open(const std::string& sFolder, const std::string& sDbName="leveldb.ldb");

        /* add new key/value to the database */
        bool Put(const std::string& sKey, const std::string& sValue, bool bSyncFlag=false);

        /* retreive single key/valie from the database */
        bool Get(const std::string& sKey, std::string& sValue);

        /* retrieve all the values associated with a key */
        bool MultiGet(const std::string& sKey, std::string& sValue);

        /* delete key/value from the database */
        bool Delete(const std::string& sKey, bool bSyncFlag=false);

        /* add new batch key/value to the database */
        bool WriteBatch(leveldb::WriteBatch& batch, bool bSyncFlag=false);

    private:
        leveldb::DB* m_pLdb;
        leveldb::Status m_status;
    };
}

#endif
