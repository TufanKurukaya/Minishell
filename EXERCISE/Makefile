all: dup2 fork pipe execve

dup2: dup2.c
	@gcc -o dup2 dup2.c

fork: fork.c
	@gcc -o fork fork.c

pipe: pipe.c
	@gcc -o pipe pipe.c

execve: execve.c print_argv.c
	@gcc -o execve execve.c
	@gcc -o print_argv print_argv.c

clean:
	@rm -f dup2 fork pipe execve print_argv

.PHONY: clean all
