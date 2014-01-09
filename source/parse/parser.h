#ifndef _H_PARSER
#define _H_PARSER


#include "platform/tlibc_platform.h"

#include <stdio.h>
#include "parse/scanner.h"
#include "protocol/tlibc_abstract_writer.h"

#include "datrie/trie.h"
#include "error/error_msg_types.h"
#include "definition.h"
#include "generator.h"
#include "symbols.h"

typedef union _PARSER_VALUE
{
	ST_Import sn_import;

	ST_TYPE sn_type;
	ST_SIMPLE_TYPE sn_simple_type;
	ST_VALUE sn_value;	
	tbytes sn_tok_identifier;

	ST_Const sn_const;

	tdouble pn_tok_double;


	const char* sn_tok_unixcomment;
	tbool sn_bool;
	tuint64 sn_uint64;
	tint64 sn_int64;
	tdouble sn_d;
	tuint64 sn_hex_uint64;
	tint64 sn_hex_int64;
	tstring sn_string;
	tchar sn_char;
	SN_SIMPLE_TYPE sn_st;


	ST_ARGUMENTS sn_arguments;
	SN_CONTAINER_TYPE sn_ct;

	ST_TYPEDEF sn_typedef;

	ST_UNIX_COMMENT sn_unix_comment;

	ST_ENUM_DEF sn_enum_def;
	ST_Parameter sn_parameter;
	ST_Parameters sn_parameters;

	ST_Expression sn_expression;
	ST_CONDITION sn_condition;

}PARSER_VALUE;

#define TD_MAX_GENERATOR 16
typedef struct _PARSER PARSER;
struct _PARSER 
{
	SCANNER_STACK scanner_stack;

	GENERATOR *generator_list[TD_MAX_GENERATOR];
	tuint32 generator_num;
		
	char file_name[MAX_FILE_NAME_LENGTH];

	//���ű�
	Trie *symbols;
	char domain[MAX_FILE_NAME_LENGTH];

	ST_DEFINITION pn_definition;
	ST_FIELD_LIST pn_field_list;
	ST_FIELD pn_field;
	tbool in_union;
	tbool in_struct;
};

void parser_init(PARSER *self);

tint32 parser_add_generator(PARSER *self, GENERATOR *generator);

tint32 parser_parse(PARSER *self, const char* file_name);

void parser_on_definition(PARSER *self, const YYLTYPE *yylloc, const ST_DEFINITION *pn_definition);

const SYMBOLS* parser_symbol_find_by_string(PARSER *self, const char* name);
const SYMBOLS* parser_symbol_find(PARSER *self, const tbytes* tok_identifier);
const SYMBOLS* parser_symbol_find_by_string_local(PARSER *self, const char* name);
const SYMBOLS* parser_symbol__find_local(PARSER *self, const tbytes* tok_identifier);

tint32 parser_symbol_save_string(PARSER *self, const char *name, const SYMBOLS *symbol);
tint32 parser_symbol_save(PARSER *self, const tbytes *tok_identifier, const SYMBOLS *symbol);
void parser_symbol_domain_begin(PARSER *self, const YYLTYPE *yylloc, const tbytes *tok_identifier);
void parser_symbol_domain_end(PARSER *self, const YYLTYPE *yylloc);

#endif//_H_PARSER

