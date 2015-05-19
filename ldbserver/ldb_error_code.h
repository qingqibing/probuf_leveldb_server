#ifndef _LDB_ERROR_CODE_H_
#define _LDB_ERROR_CODE_H_
#include <stdint.h>

typedef enum
{
    GET_CMD    =  1,
    PUT_CMD    =  2,
    DELETE_CMD =  3,

} ELdbApiCmd;

typedef enum
{
    LDB_SERVER_SUCCESS           = 1,
    LDB_SERVER_GET_FAIL         = 1001,
    LDB_SERVER_PUT_FAIL         = 1002,
    LDB_SERVER_DELETE_FAIL      = 1003,
    LDB_SERVER_KEY_IS_NULL      = 1004,
    LDB_SERVER_VALUE_IS_NULL    = 1005,
    LDB_SERVER_ILLEGAL_CMDID    = 1006,
} ELdbServerErrorCode;

#endif
