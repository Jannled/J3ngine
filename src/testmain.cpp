#include <stdio.h>

#include "Info.h"

void main(int argc, char** argv)
{
    printf("J3Engine Version %d.%d.%d launched with %d params!", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, argc);
}