#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc > 1)
		while (argv[++i])
			printf("\033[1;32m%s\033[0m\n", argv[i]);
	else
		printf("\033[1;31mNo arguments\033[0m\n");
	return (0);
}
