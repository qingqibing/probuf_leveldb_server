#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <iostream>
#include <leveldb/db.h>
#include <leveldb/status.h>
#include <leveldb/write_batch.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

#include "ldbdata.pb.h"
#include "ldb_error_code.h"

class CCommand
{
public:
    CCommand();
    virtual ~CCommand();
    virtual void execute()=0;

public:
    virtual void SetRequestParam(ldbdata::Request& Request);
    virtual void SetResponseParam(ldbdata::Response& Response);

protected:
    ldbdata::Request m_oRequest;
    ldbdata::Response m_oResponse;
    leveldb::DB* m_pLdb;
    leveldb::Status m_status;
};


#endif
