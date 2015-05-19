#include "Command.h"

CCommand::CCommand()
{
}

CCommand::~CCommand()
{
}

void CCommand::SetRequestParam(ldbdata::Request& Request)
{
    m_oRequest = Request;
}

void CCommand::SetResponseParam(ldbdata::Response& Response)
{
    Response = m_oResponse;
}
