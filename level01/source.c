#include <stdio.h>
#include <string.h>

char a_user_name[256];

int verify_user_name(void){
    puts("verifying username....\n");
    return (strncmp(a_user_name, "dat_wil", 7));
}

int verify_user_pass(char *password){
    return (strncmp(password, "admin", 5));
}

int main(void){
	char password[64];
	
	bzero(password, 64);

	puts("********* ADMIN LOGIN PROMPT *********");
	puts("Enter Username: ");
	fgets(a_user_name, 256, stdin);

	if (verify_user_name() == 0) {
		puts("Enter Password: ");
		fgets(password, 100, stdin);
		if (verify_user_pass(password) == 0 || verify_user_pass(password) != 0)
			puts("nope, incorrect password...\n");
	}
	else {
		puts("nope, incorrect username...\n");
	}

	return (0);
}
