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
  while ((character = getopt (argc, argv, "d:m:rte")) != -1)
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
      case 'e':
        arguments.action = TRAIN_EMBEDDED;
        break;
      case 't':
        arguments.action = TRAIN;
        break;
      case '?':
        if (optopt == 'd')
          arguments.data_dir_path = 0;
    }
  if(arguments.action == UNSET)
    printf("\x1B[31m[ERROR]\x1B[0m You need to set a mode with -r or -t (RUN, TRAIN)\n");
  if(arguments.action == RUN && arguments.model_file_path == 0)
    printf("\x1B[31m[ERROR]\x1B[0m You need to specify a model path with -m\n");
  if(arguments.action == TRAIN && arguments.data_dir_path == 0)
    printf("\x1B[31m[ERROR]\x1B[0m You need to specify a training data path with -d\n");

  return arguments;
}