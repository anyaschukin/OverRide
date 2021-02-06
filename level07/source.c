#include <stdio.h>
#include <string.h>

void	clear_stdin(void)
{
	char	x = 0;

	while (1)
	{
		x = getchar();
		if (x == '\n' || x == EOF)
			break ;
	}
}

unsigned int	get_unum(void)
{
	unsigned int	input;

	fflush(stdout);
	scanf("%u", &input);
	clear_stdin();
	return (input);
}

int	store_number(int *tab)
{
	unsigned int	input = 0;
	unsigned int	index = 0;

	// Read input and index
	printf(" Number: ");
	input = get_unum();
	printf(" Index: ");
	index = get_unum();

	// Reserved for wil!
	if ( index % 3 == 0 || (input >> 24) == 183)
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}

	// store number in index
	tab[index] = input;
	return (0);
}

int	read_number(int *tab)
{
	unsigned int	input = 0;

	printf(" Index: ");
	input = get_unum();
	printf(" Number at data[%u] is %u\n", input, tab[input]);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	// initialize variables
	int		ret = 0;
	char	buffer[20] = {0};
	int		tab[100] = {0};

	// zero argv & and env
	for (int i = 0; argv[i] != 0; i++)
		memset(argv[i], 0, strlen(argv[i]) - 1);
	for (int i = 0; env[i] != 0; i++)
		memset(env[i], 0, strlen(env[i] - 1));

	puts("----------------------------------------------------\n"\
		 "  Welcome to wil's crappy number storage service!   \n"\
		 "----------------------------------------------------\n"\
		 " Commands:                                          \n"\
		 "    store - store a number into the data storage    \n"\
		 "    read  - read a number from the data storage     \n"\
		 "    quit  - exit the program                        \n"\
		 "----------------------------------------------------\n"\
		 "   wil has reserved some storage :>                 \n"\
		 "----------------------------------------------------\n"\
		 "\n");

	// Command loop
	while (1)
	{
		printf("Input command: ");
		ret = 1;
		fgets(buffer, 20, stdin);
		buffer[strlen(buffer) - 1] = 0;
		if (strncmp("store", buffer, 5) == 0)
			ret = store_number(tab);				// store
		else if (strncmp("read", buffer, 4) == 0)
			ret = read_number(tab);					// read
		else if (strncmp("quit", buffer, 4) == 0)
			return (0);								// quit
		if (ret != 0)
			printf(" Failed to do %s command\n", buffer);
		else
			printf(" Completed %s command successfully\n", buffer);
		bzero(buffer, 20);
	}
	return (0);
}
