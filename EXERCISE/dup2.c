#include <fcntl.h>
#include <unistd.h>

// int main()
// {
// 	int fd1 = open("file1.txt", O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0644);
// 	write(1, "Merhabalar\n", 11);
// 	write(fd1, "Hello, World!\n", 14);
// 	dup2(fd1, 1);
// 	close(fd1);
// 	write(1, "Naber, Dunya!\n", 14);
// }

// int main()
// {
// 	int fd1 = open("file1.txt", O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0644);
// 	int fd2 = open("file2.txt", O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0644);

// 	write(fd1, "file1.txt = ", 12);
// 	write(fd2, "file2.txt = ", 12);

// 	dup2(fd1, fd2);

// 	write(fd1, "Hello, World!\n", 14);
// 	write(fd2, "Naber, Dunya!\n", 14);

// 	close(fd1);
// 	close(fd2);
// }

// int main ()
// {
// 	int fd[2];
// 	pipe(fd);

// 	write(fd[1], "Hello, World!", 13);
// 	close(fd[1]); // fd[1]'i kapatın, çünkü yazma işlemi tamamlandı

// 	dup2(fd[0], 0); // fd[0]'ı stdin (0) dosya tanımlayıcısına kopyalayın
// 	close(fd[0]); // fd[0]'ı kapatın, çünkü artık stdin olarak kullanılacak

// 	execlp("cat", "cat", NULL); // cat programını çalıştırın

// 	return (0);
// }

int	main(void)
{
	int	fd1;
	int	fd2;

	fd1 = open("file1.txt", O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0644);
	fd2 = open("file2.txt", O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0644);
	write(fd1, "Hello, World!", 13); // file1.txt dosyasına yazı yaz
	dup2(fd1, fd2);                 
		// file1.txt dosyasını file2.txt dosyasına kopyala
	close(fd1);                      // file1.txt dosyasını kapat
	write(fd2, "Naber, Dunya!", 13);
		// file2.txt dosyasına yazı yaz fakat dup2 kullanildigi icin file1.txt dosyasina yazilacak
	close(fd2);                      // file2.txt dosyasını kapat
}
