#ifndef _PUT_COMMAND_H_
#define _PUT_COMMAND_H_

#include "Command.h"

class CPutCommand : public CCommand
{
public:
    CPutCommand();
    explicit CPutCommand(leveldb::DB* pLdb);
    virtual ~CPutCommand();
    void execute();
};

#endif
