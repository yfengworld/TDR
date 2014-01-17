#include <stdio.h>
#include "parse/parser.h"
#include "language/language.h"
#include "version.h"


#include "generate/tlibc_types.h"
#include "generate/tlibc_reader.h"
#include "generate/tlibc_reader_header.h"
#include "generate/tlibc_writer.h"
#include "generate/tlibc_writer_header.h"


#include <string.h>
#include "globals.h"

//���ι��
#pragma warning (disable: 4996)

void version()
{
	printf("TData version %s\n", TDATA_VERSION);
}

void usage()
{
	fprintf(stderr, "Usage: tdata [options] file\n\n");
	fprintf(stderr, "Use tdata -help for a list of options\n");
}

void help()
{
	fprintf(stderr, "Usage: tdata [options] file\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "  -version					Print the compiler version\n");
	fprintf(stderr, "  -gen types				Gen source\n");
	fprintf(stderr, "  -s dir					Set the source directory\n");
	fprintf(stderr, "  -t dir					Set the target directory\n");
}

#define TD_MAX_GENERATOR 16

static PARSER parser;
static ST_TD_LANGUAGE_STRING_LIBRARY language_string_library;
static TLIBC_TYPES_GENERATOR tlibc_types_generator;
static TLIBC_READER_GENERATOR tlibc_reader_generator;
static TLIBC_READER_HEADER_GENERATOR tlibc_reader_header_generator;
static TLIBC_WRITER_GENERATOR tlibc_writer_generator;
static TLIBC_WRITER_HEADER_GENERATOR tlibc_writer_header_generator;

static GENERATOR *generator_list[TD_MAX_GENERATOR];
static tuint32 generator_num = 0;
int main(tint32 argc, char **argv)
{
	tint32 i;

	if(language_string_library_init(&language_string_library) != E_TD_NOERROR)
	{
		fprintf(stderr, "Can not load language!\n");
		goto ERROR_RET;
	}
	g_language_string_library = &language_string_library;

	parser_init(&parser);
	for (i = 1; i < argc; ++i)
	{
		char* arg;

		arg = strtok(argv[i], " ");
		if (arg[0] == '-' && arg[1] == '-')
		{
			++arg;
		}
		if (strcmp(arg, "-help") == 0)
		{
			help();
			goto ERROR_RET;
		}
		else if (strcmp(arg, "-version") == 0)
		{
			version();
			goto ERROR_RET;
		}
		else if (strcmp(arg, "-s") == 0)
		{			
			g_source_dir = argv[++i];
			if (g_source_dir == NULL)
			{
				fprintf(stderr, "Missing source directory specification\n");
				usage();
				goto ERROR_RET;
			}
		}
		else if (strcmp(arg, "-t") == 0)
		{
			g_target_dir = argv[++i];
			if (g_target_dir == NULL)
			{
				fprintf(stderr, "Missing target directory specification\n");
				usage();
				goto ERROR_RET;
			}
		}
		else if (strcmp(arg, "-gen") == 0)
		{
			arg = argv[++i];
			if(strcmp(arg, "tlibc") == 0)
			{
				tlibc_types_generator_init(&tlibc_types_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_types_generator.super;

				tlibc_reader_generator_init(&tlibc_reader_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_reader_generator.super;

				tlibc_reader_header_generator_init(&tlibc_reader_header_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_reader_header_generator.super;

				tlibc_writer_generator_init(&tlibc_writer_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_writer_generator.super;

				tlibc_writer_header_generator_init(&tlibc_writer_header_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_writer_header_generator.super;
			}
			else if(strcmp(arg, "tlibc_types") == 0)
			{
				tlibc_types_generator_init(&tlibc_types_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_types_generator.super;
			}
			else if(strcmp(arg, "tlibc_reader") == 0)
			{
				tlibc_reader_generator_init(&tlibc_reader_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_reader_generator.super;

				tlibc_reader_header_generator_init(&tlibc_reader_header_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_reader_header_generator.super;
			}
			else if(strcmp(arg, "tlibc_writer") == 0)
			{
				tlibc_writer_generator_init(&tlibc_writer_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_writer_generator.super;

				tlibc_writer_header_generator_init(&tlibc_writer_header_generator, &parser.symbols);
				generator_list[generator_num++] = &tlibc_writer_header_generator.super;
			}
		}		
		else
		{
			break;
		}
	}

	if(generator_num == 0)
	{
		fprintf(stderr, "Missing -gen types\n");
		help();
		goto ERROR_RET;
	}

	for(; i < argc; ++i)
	{
		if(parser_parse(&parser, argv[i], generator_list, generator_num) != E_TD_NOERROR)
		{
			goto ERROR_RET;
		}
	}

	return 0;
ERROR_RET:
	return 1;
}
