#ifndef _DELETE_COMMAND_H
#define _DELETE_COMMAND_H

#include "Command.h"

class CDeleteCommand : public CCommand
{
public:
    CDeleteCommand();
    explicit CDeleteCommand(leveldb::DB* pLdb);
    virtual ~CDeleteCommand();
    void execute();
};

#endif
