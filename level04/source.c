#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <linux/ptrace.h>

int	main(void)
{
	// Fork process
	int		child_pid = fork();

	// Initialize variables
	char	buffer[32];
	bzero(buffer, 32);
	int		ptrace_ret = 0;
	int		status = 0;

	if (child_pid == 0)
	{
		// Link child process return
		prctl(1, 1);
		ptrace(0, 0, 0, 0);
		// Read stdin into buffer
		puts("Give me some shellcode, k");
		gets(buffer);
		return (0);
	}

	// Wait for child process to exit
	while (ptrace_ret = ptrace(PTRACE_PEEKUSR, child_pid, 44, 0) != 11)
	{
		wait(&status);
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			puts("child is exiting...");
			return (0);
		}
	}
	// Kill child process if it calls exec()
	puts("no exec() for you");
	kill(child_pid, 9);
	return (0);
}
