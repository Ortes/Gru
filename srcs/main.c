#include "arg.h"
#include "data.h"

int main(int argc, char* const argv[]) {
    Arguments arguments = arguments_get_args(argc, argv);
    data_init(arguments);
}