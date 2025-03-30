#include <X11/X.h>
#include <type_traits>

#define MOD	 Mod1Mask
#define NULL 0

/* Thanks suckless! */
typedef union {
	int i;
	unsigned int ui;
	float f;
	const void *v;
} Arg;

typedef struct {
	unsigned int mask;
	KeySym key;
	void (*fn) (Arg*);
} Bind;

/* Commands */
static const char *termcmd[] = { "st", NULL };

#include <X11/keysym.h>
#include <X11/XF86keysym.h>
static const Bind keybinds[] = {
	{MOD|ShiftMask,		XK_A,		spawn,		{.v = termcmd}}
};
