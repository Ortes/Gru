#include <stdio.h>
#include <unistd.h>

#include "arg.h"

// TODO display usages.
Arguments arguments_get_args(int argc, char* const argv[]) {
  Arguments arguments;
  arguments.action = UNSET;
  arguments.data_dir_path = 0;
  arguments.model_file_path = 0;
  char character;
  while ((character = getopt (argc, argv, "d:m:rt")) != -1)
    switch (character)
    {
      case 'd':
        arguments.data_dir_path = optarg;
        break;
      case 'm':
        arguments.model_file_path = optarg;
        break;
      case 'r':
        arguments.action = RUN;
        break;
      case 't':
        arguments.action = TRAIN;
      case '?':
        if (optopt == 'd')
          arguments.data_dir_path = 0;
    }
  if(arguments.action == UNSET)
    printf("You need to set a mode with -r or -t (RUN, TRAIN)\n");
  if(arguments.action == RUN && arguments.model_file_path == 0)
    printf("You need to specify a model path with -m\n");
  if(arguments.action == TRAIN && arguments.data_dir_path == 0)
    printf("You need to specify a training data path with -d\n");

  return arguments;
}