#include <unistd.h>
#include <sys/wait.h>
// execve calıştığında hatalı bir durum oluşursa -1 döndürür
// execve fonksiyonu başarılı olursa geri dönmez ve çalışan işlemi sonlandırır
int	main(void)
{
	char	*argv[] = {"pint_argv", "Merhaba", "Dünya", NULL}; // print_args programina gonderilecek argumanlari belirledik
	int		pid;

	pid = fork();
	if (pid == 0)
		execve("print_argv", argv, NULL); // print_args programini calistir
	else
		waitpid(pid, NULL, 0);
}

// int	main(void)
// {
// 	char **argv = {"/bin/ls","-ls",NULL}; // çalışacak programa gönderilecek argümanlari belirledik
// 	execve(argv[0], argv, NULL); // belirledigimiz programini calistir
// 	printf("execve failed\n"); // execve basarisiz olursa bu satir calisir
// 	//eger basarili olursa execvenin calıştığı process tamamen sonlanır
// }

