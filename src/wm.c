#include <stdio.h>
#include <string.h>

#define WM_NAME		"XWM"
#define VER			"0.1.0"
#define OWNERSHIP	"© uint23 2025"

static void run();

static void run()
{
	for (;;)
	{
		getc(stdin);
	}
}

int
main(int ac, char **av)
{
	if (ac == 2) {
		if (strcmp(av[1], "-v") == 0 ||
			strcmp(av[1], "--version") == 0) {
			printf("%s ver %s\n%s\n",WM_NAME, VER, OWNERSHIP );

		}  else if (strcmp(av[1], "--help")  == 0 ||
					strcmp(av[1], "-h") == 0) {
			puts("idk...");
		
		} else {
			printf("USEAGE:\n\t[-v || --version]: Get the version of %s\n\t[-h || --help]: Get help\n", WM_NAME);
		}

	} else if (ac > 2) {
		puts("Too many args\nExiting...");
	} else if (ac == 1) {
		run();
	}

	return 0;

}
