#include <fcntl.h>
#include <unistd.h>

// int	main(void)
// {
// 	int		pipfd[2];
// 	char	buf[100];

// 	if (pipe(pipfd) == -1)
// 		return (1);
// 	write(pipfd[1], "Hello, World!", 13);// pipfd[1]'e yaz
// 	read(pipfd[0], buf, 13); // pipfd[0]'dan pipfd[1]'e yazilan veriyi oku
// 	write(1, buf, 13); // buf'a yazılan veriyi yaz
// }

// close islemlerini lsof ile kontrol edebilirsiniz
int	main(void)
{
	int	pipfd[2];

	if (pipe(pipfd) == -1)
		return (1);
	write(pipfd[1], "Hello, World!", 13);
	close(pipfd[1]); // pipfd[1]'i kapatın, çünkü yazma işlemi tamamlandı
	dup2(pipfd[0], 0); // pipfd[0]'ı stdin (0) dosya tanımlayıcısına kopyalayın
	close(pipfd[0]); // pipfd[0]'ı kapatın, çünkü artık stdin olarak kullanılacak
	execlp("cat", "cat", NULL); // burada cat programını çalıştırın veya standart inputu okuyun herhangi bir program çalıştırabilirsiniz
}
