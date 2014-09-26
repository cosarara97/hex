#include <cstdlib>
#include <cstring>
#include <iostream>

#include <argp.h>

using namespace std;

#include "cli.h"
#include "editor.h"

static struct argp_option options[] = {
	{"table", 't', "TABLE", 0},
	{ 0 }
};

struct arguments {
	char* file_name;
	char* table;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *args = (arguments*)(state->input);

  switch (key)
    {
    case 't':
      args->table = arg;
      break;

    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        /* Too many arguments */
        argp_usage (state);

      args->file_name = arg;
      break;

    case ARGP_KEY_END:
      if (state->arg_num == 0)
        /* No filename */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static const char* args_doc = "FILE";
static struct argp argp = { options, parse_opt, args_doc, 0};


void CLI::Run (int argc, char ** argv)
{
  Editor editor;
  struct arguments arguments;
  arguments.table = 0;
  argp_parse (&argp, argc, argv, 0, 0, &arguments);
  std::cout << arguments.file_name << std::endl;
  if (arguments.table != 0) {
    std::cout << arguments.table << std::endl;
  }

  // Initialize editor
  editor.Init();

  editor.OpenFile(arguments.file_name);

  // editor.LoadEncodingTable(arguments.table);

  // Start editor
  editor.Run();

}

static void print_version (FILE *stream, struct argp_state *state) {
        fprintf(stream,
          " __  __                              \n"
          "/\\ \\/\\ \\                         \n"
          "\\ \\ \\_\\ \\     __   __  _        \n"
          " \\ \\  _  \\  /'__`\\/\\ \\/'\\     \n"
          "  \\ \\ \\ \\ \\/\\  __/\\/>  </     \n"
          "   \\ \\_\\ \\_\\ \\____\\/\\_/\\_\\ \n"
          "    \\/_/\\/_/\\/____/\\//\\/_/      \n\n");
	cout << VERSION << endl;
	exit(EXIT_SUCCESS);
}

void (*argp_program_version_hook) (FILE *, struct argp_state *) = print_version;

