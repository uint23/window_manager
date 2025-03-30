#include "utils.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

void
succumb(char *message, int exit_code)
{
	puts(message);
	exit(exit_code);
}
