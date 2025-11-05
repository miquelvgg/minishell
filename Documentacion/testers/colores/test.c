#include "colors.h"

int	main()
{
	print_msg("test", EXIT_SUCCESS);
	print_msg("test", EXIT_FAILURE);
	print_msg("test", MESSAGE);

	printf("%s%stest%s\n", BLACK, BG_MAGENTA, RESET);
	printf("%stest%s\n", RED, RESET);
	printf("%stest%s\n", GREEN, RESET);
	printf("%stest%s\n", YELLOW, RESET);
	printf("%stest%s\n", BLUE, RESET);
	printf("%stest%s\n", MAGENTA, RESET);
	printf("%stest%s\n", CYAN, RESET);
	printf("%stest%s\n", WHITE, RESET);

	printf("%stest%s\n", BG_BLACK, RESET);
	printf("%stest%s\n", BG_RED, RESET);
	printf("%stest%s\n", BG_GREEN, RESET);
	printf("%stest%s\n", BG_YELLOW, RESET);
	printf("%stest%s\n", BG_BLUE, RESET);
	printf("%stest%s\n", BG_MAGENTA, RESET);
	printf("%stest%s\n", BG_CYAN, RESET);
	printf("%stest%s\n", BG_WHITE, RESET);
}
