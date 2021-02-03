#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/ptrace.h>

int	auth(char *login, int serial)
{
	login[strcspn(login, "\n")] = 0;
	int	len = strnlen(login, 32);
	if (len > 5)
	{
		// Detect tampering
		if (ptrace(0, 0, 1, 0) == -1)
		{
			puts("\033[32m.----------------------------.");
			puts("\033[31m| !! TAMPERING DETECTED !!  |");
			puts("\033[32m'----------------------------'");
			return (1);
		}

		// Seed hash
		int	hash = (login[3] ^ 4919) + 6221293;
		// Hashing loop interates through login
		int	i = 0;
		while (i < len)
		{
			// Reject non-printable login
			if (login[i] <= 31)
				return (1);
			// Hashing algo
			hash += hash_chunk(login[i]);
			i++;
		}

		// Compare serial and hash
		if (serial != hash)
			return (1);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	// Read Login from stdin
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	char	login[32];
	fgets(login, 32, stdin);

	// Read Serial from stdin
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	int		serial;
	scanf("%u", &serial);

	// Authenticate Login and Serial
	if (auth(login, serial) == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
		return (0);
	}
	return (1);
}
