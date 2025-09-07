CC = gcc
CFLAGS = -g -Wall
RM = rm -f

# Obtém todos os arquivos .c no diretório atual
SOURCES := $(wildcard *.c)

# Obtém o nome dos programas alvo
PROGRAMS := $(SOURCES:.c=)

all: $(PROGRAMS)

# Regra de compilação genérica
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(PROGRAMS)


# A linha PROGRAMS := $(SOURCES:.c=) é uma declaração no Makefile que usa uma técnica chamada "Substituição de Sufixo" ou "Substituição de Extensão".
# A variável SOURCES contém uma lista de todos os arquivos .c presentes no diretório atual. 
# Por exemplo, se houver três arquivos .c no diretório (prog1.c, prog2.c e prog3.c), então SOURCES seria igual a prog1.c prog2.c prog3.c.
# A expressão $(SOURCES:.c=) diz ao Make para criar uma nova lista de arquivos baseada em SOURCES, 
# mas substituindo a extensão .c de cada arquivo por nada (vazio).
# Então, se aplicarmos essa substituição na lista SOURCES, 
# obteremos a lista de programas alvo PROGRAMS. 
# Usando o exemplo acima, a substituição resultaria em prog1 prog2 prog3. 
# Agora, a variável PROGRAMS contém uma lista de todos os programas alvo que desejamos compilar.