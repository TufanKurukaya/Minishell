#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	int		pid;
	char	*message;

	message = (char *)malloc(20);
	pid = fork();
	if (pid == -1) // fork fonksiyonu başarısız olursa -1 döndürür
		return (1);
	if (pid == 0) // bu if bloğunda yapılan tüm işlemler child process için yapılıyor
	{
		strcpy(message, "This is the child");
		printf("PID		=	[%d]\n", pid);
		printf("Value		=	\"%s\"\n", message);
		printf("Adress		=	[%p]\n", message);
		printf("PointerAdress	=	[%p]\n", &message);
		free(message); // bu satırnın normalde olması gerekiyor kaldirip valgrind ile teset edebilirsiniz
	}
	else
	{
		waitpid(pid, NULL, 0); // belirtilen pid'li child processin bitmesini bekler
		strcpy(message, "This is the parent");
		printf("PID		=	[%d]\n", pid);
		printf("Value		=	\"%s\"\n", message);
		printf("Adress		=	[%p]\n", message);
		printf("PointerAdress	=	[%p]\n", &message);
		free(message); // bu satırnın normalde olması gerekiyor kaldirip valgrind ile teset edebilirsiniz
	}
}
