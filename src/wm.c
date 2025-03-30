#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

#include "utils.h"

#define WM_NAME		"XWM"
#define VER			"0.1.0"
#define OWNERSHIP	"© uint23 2025"

static void run();

static Display *dpy 	= NULL;
static Window 	root	= (unsigned long) NULL;

static void
run()
{
	/* Initial checks etc */
	dpy = XOpenDisplay(NULL);
	if (dpy == 0)
		succumb("Can't open display :(\n", EXIT_FAILURE);

	int scr = XDefaultScreen(dpy);
	root = RootWindow(dpy, scr);
	XEvent ev;

	XSelectInput(dpy, root,
			SubstructureRedirectMask | SubstructureNotifyMask
			);


	/* Main loop */
	for (;;)
	{
		XNextEvent(dpy, &ev);
	}
}

int
main(int ac, char **av)
{
	if (ac == 2) {
		if (strcmp(av[1], "-v") == 0 ||
			strcmp(av[1], "--version") == 0)
			printf("%s ver %s\n%s\n",WM_NAME, VER, OWNERSHIP );

		else if (strcmp(av[1], "--help")  == 0 ||
					strcmp(av[1], "-h") == 0)
			puts("idk...");
		
		else
			printf("USEAGE:\n\t[-v || --version]: Get the version of %s\n\t[-h || --help]: Get help\n", WM_NAME);

	}

	else if (ac > 2)
		puts("Too many args\nExiting...");

	else
		run();

	XCloseDisplay(dpy);
	return EXIT_SUCCESS;
}
