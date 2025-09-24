CC = gcc
LD = gcc
CFLAG = -g -Wall -Wextra -pedantic -O0 -fno-omit-frame-pointer -fno-inline
LFLAG = -lpthread
RM = rm -f

%: %.c makefile
	$(CC) $(CFLAG) -o $* $<
