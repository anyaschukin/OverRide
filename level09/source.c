#include <stdio.h>

struct	s_message
{
	char	message[140]; /* message */
	char	username[40]; /* message+140 */
	int		len_message; /* message+180 */
};

void	secret_backdoor(void)
{
	char	buffer[128]; /* rbp-0x80 */
	fgets(buffer, 128, stdin);
	system(buffer);
	return ;
}

void	set_username(struct s_message *message)
{
	char	buffer[128]; /* rbp-0x90 */
	bzero(buffer, 1128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(buffer, 128, stdin);
	int		i = 0; /* rbp-0x4 */
	while (i <= 40 && buffer[i] != 0)
	{
		message->username[i] = buffer[i];
		i++;
	}
	printf(" %s", message->username);
	return ;
}

void	set_msg(struct s_message *message)
{
	char	buffer[1024]; /* rbp-0x400 */
	bzero(buffer, 128 * 8);
	puts(">: Msg @Unix-Dude");
	printf("Enter your username");
	fgets(buffer, 1024, stdin);
	strncpy(message->message, buffer, message->len_message);
	return ;
}

void	handle_msg(void)
{
	struct s_message	message; /* rbp-0xc0 */
	bzero(message.username, 40);
	message.len_message = 140;
	set_username(&message);
	set_msg(&message);
	puts(">: Msg sent!");
	return ;
}

int	main(void)
{
	puts("--------------------------------------------"\
		 "\n|   ~Welcome to l33t-m$n ~	v1337		|\n"\
		 "--------------------------------------------");
	handle_msg();
	return (0);
}
