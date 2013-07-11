#ifndef _H_LANGUAGE_TYPES
#define _H_LANGUAGE_TYPES

#include "hotpot/hp_platform.h"
#include "hotpot/hp_error.h"

#define MAX_LANGUAGE_STRING_NUM 10240
#define MAX_LANGUAGE_STRING_LENGTH 1024
typedef enum _LanguageStringID
{
	E_SID_NOERROR = E_HP_NOERROR,
	E_SID_ERROR = E_HP_ERROR,
	E_SID_CONSTANT_REDEFINITION = E_HP_CONSTANT_REDEFINITION,
	E_SID_INTEGER_OVERFLOW = E_HP_INTEGER_OVERFLOW,
	E_SID_CAN_NOT_OPEN_FILE = E_HP_CAN_NOT_OPEN_FILE,
	E_SID_CAN_NOT_FIND_CONSTANCE = E_HP_CAN_NOT_FIND_CONSTANCE,
}LanguageStringID;

typedef struct _LanguageString
{
	LanguageStringID sid;
	hpchar str[MAX_LANGUAGE_STRING_LENGTH];
}LanguageString;

typedef struct _LanguageLib
{
	hpuint32 str_num;
	LanguageString str[MAX_LANGUAGE_STRING_NUM];
}LanguageLib;

#endif//_H_LANGUAGE_TYPES
