#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void decrypt(key)
{
	char *crypt = "Q}|u`sfg~sf{}|a3";
	size_t len;
	size_t i;
	
	len = strlen(crypt);
	i = 0;
	
	while (i < len) {
		crypt[i] = crypt[i] ^ key;
		i++;
	}
	
	if (strncmp(crypt, "Congratulations", 17) == 0) {
    	system("/bin/sh");
	}
	else {
		puts("\nInvalid Password");
	}

	return ;
}

void test(int input, int number)
{
	int key;
	
	key = number - input;
	if (key > 21) {
		decrypt(rand());
	}
	decrypt(key);
	return ;
}

int main(void)
{
  int     input;

  srand(time(0));

  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");

  scanf("%d", &input);
  test(input, 322424845);
  return (0);
}
