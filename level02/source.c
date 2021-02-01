#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
// Initialize variables
	char	username[100];
	bzero(&username, 12);
	char	password[48];
	bzero(&password, 5);
	char	user_pass[112];
	bzero(&user_pass, 12);
	int		pass_len;
	FILE	*file;

// Read password from file
	file = fopen("/home/users/level03/.pass", "r");
	if (!file)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	pass_len = fread(&password, 1, 41, file);
	password[strcspn(password, "\n")] = 0;
	if (pass_len != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(1);
	}
	fclose(file);

// Read username and user_pass from stdin
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(username, 100, stdin);
	username[strcspn(username, "\n")] = 0;
	printf("--[ Password: ");
	fgets(user_pass, 100, stdin);
	user_pass[strcspn(user_pass, "\n")] = 0;
	puts("*****************************************");

// Validate Password
	if (strncmp(password, user_pass, 41))
	{
		printf(username);
		puts(" does not have access!");
		exit(1);
	}

// Open shell
	printf("Greetings, %s!\n", username);
	system("/bin/sh");
	return (0);
}
