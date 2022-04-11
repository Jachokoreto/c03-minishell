#include <unistd.h>

int	exe_redir_bi()
{
	int saved_stdout;

	/* Save current stdout for use later */
	saved_stdout = dup(1);
	dup2(my_temporary_stdout_fd, 1);

	//execve(x);
	/* Restore stdout */
	dup2(saved_stdout, 1);
	close(saved_stdout);
}