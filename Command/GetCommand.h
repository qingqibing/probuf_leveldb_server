#ifndef _GET_COMMAND_H
#define _GET_COMMAND_H

#include "Command.h"

class CGetCommand : public CCommand
{
public:
    CGetCommand();
    CGetCommand(leveldb::DB* pLdb);
    virtual ~CGetCommand();
    void execute();
};

#endif
