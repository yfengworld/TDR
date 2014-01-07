#ifndef _H_hotlib_hp_error_msg_hd_TYPES
#define _H_hotlib_hp_error_msg_hd_TYPES
#include "platform/tlibc_platform.h"
#include "error/error_code.h"
#define TD_MAX_ERROR_MSG_LENGTH 1024
typedef struct  _TD_ERROR_MSG
{
    TD_ERROR_CODE error_code;
    tchar error_msg[TD_MAX_ERROR_MSG_LENGTH];
}TD_ERROR_MSG;
typedef struct  _TD_ERROR_MSG_LIBRARY
{
	tuint32 error_list_num;
    TD_ERROR_MSG error_list[TLIBC_ERROR_CODE_NUM];
}TD_ERROR_MSG_LIBRARY;
#endif//_H_hotlib_hp_error_msg_hd_TYPES