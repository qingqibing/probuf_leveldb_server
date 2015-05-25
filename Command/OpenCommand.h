#ifndef _OPEN_COMMAND_H_
#define _OPEN_COMMAND_H_

#include "Command.h"

class COpenCommand: public CCommand
{
public:
    COpenCommand();
    virtual ~COpenCommand();
    void execute();

private:
    leveldb::DB* GetLdbHandler(const std::string& sFolder, const std::string& sDbName);
};

#endif
