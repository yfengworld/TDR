/**
 * Autogenerated by TData Compiler (0.0.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#ifndef _H_ERROR_ERROR_MSG_TYPES_H
#define _H_ERROR_ERROR_MSG_TYPES_H

#include "platform/tlibc_platform.h"


#include "error/error_code_types.h"

#define TD_MAX_ERROR_MSG_LENGTH 1024

typedef struct _TD_ERROR_MSG TD_ERROR_MSG;
struct _TD_ERROR_MSG
{
	TD_ERROR_CODE error_code;
	tchar error_msg[TD_MAX_ERROR_MSG_LENGTH];
};

typedef struct _TD_ERROR_MSG_LIBRARY TD_ERROR_MSG_LIBRARY;
struct _TD_ERROR_MSG_LIBRARY
{
	tuint32 error_list_num;
	TD_ERROR_MSG error_list[TD_ERROR_CODE_NUM];
};

#endif //_H_ERROR_ERROR_MSG_TYPES_H
