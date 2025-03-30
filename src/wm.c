#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/keysym.h>

#include "config.h"
#include "utils.h"

#define WM_NAME		"XWM"
#define VER			"0.1.0"
#define OWNERSHIP	"© uint23 2025"

static Bool checks();
static void checkev(XEvent *ev);
static void grabkeys();
static void mapwindow(Window w);
static void run();
static void selinputs();
static void spawn(Arg *arg);

static Window 	root;
static Display *dpy 	= NULL;
static Bool		running	= False;

static Bool
checks()
{
	/* Initial checks etc */
	return True;
}

static void
checkev(XEvent *ev)
{
	switch (ev->type) {
	case MapRequest:
		XMapWindow(dpy, ev->xmaprequest.window);
		break;

	default:
		puts("NOT A SELECTED INPUT");
		break;

	}
}

static void
grabkeys()
{
	// TODO
}

static void
mapwindow(Window w)
{
	XWindowAttributes wa;
	XGetWindowAttributes(dpy, w, &wa);

	/* Make the window spawn in the middle */
	int win_width = wa.screen->width / 2;
	int win_height = wa.screen->height / 2;

	// Center position
	int x = (wa.screen->width - win_width) / 2;
	int y = (wa.screen->height - win_height) / 2;

	XMoveResizeWindow(dpy, w, x, y, win_width, win_height);
	XMapWindow(dpy, w);
}

static void
run()
{
	dpy = XOpenDisplay(NULL);
	if (dpy == 0)
		succumb("Can't open display :(\n", EXIT_FAILURE);

	int scr = XDefaultScreen(dpy);
	root = RootWindow(dpy, scr);
	XEvent ev;
	selinputs();

	/* Main loop */
	while (running)
	{
		XNextEvent(dpy, &ev);
		checkev(&ev);
	}
}

static void
selinputs()
{
	XSelectInput(
		dpy,
		root,
		SubstructureRedirectMask |    // Intercept map/configure requests
		SubstructureNotifyMask   |    // Listen to child window events
		StructureNotifyMask      |    // Listen for destroy/configure events
		PropertyChangeMask       |    // Detect WM_NAME, WM_HINTS, etc
		ButtonPressMask          |    // Mouse clicks
		ButtonReleaseMask        |    // Mouse release
		PointerMotionMask        |    // Mouse movement
		EnterWindowMask          |    // Pointer enters window
		LeaveWindowMask          |    // Pointer leaves window
		FocusChangeMask          |    // FocusIn/Out events
		KeyPressMask             |    // Keyboard input
		KeyReleaseMask                // Key release
	);
}

static void
spawn(Arg *arg)
{
	// TODO
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

	else {
		if (!checks())
			XCloseDisplay(dpy);
		run();
	}

	XCloseDisplay(dpy);
	return EXIT_SUCCESS;
}
