#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	password;

	puts("***********************************");
	puts("* \t	 -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &password);
	if (password == 0x149c)
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
		return (0);
	}
	puts("\nInvalid Password!");
	return (1);
}
