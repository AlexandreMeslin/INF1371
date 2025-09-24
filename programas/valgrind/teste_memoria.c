#include <stdio.h>
#include <stdlib.h>

void func_com_vazamento();
void func_uso_apos_free();

/**
 * Programa para testar várias situações de memória com Valgrind
 * Inclui vazamento de memória, uso após free e acesso a memória não inicializada.
 * Compilar:
 *   gcc -g -Wall -Wextra -pedantic -O0 -fno-omit-frame-pointer -fno-inline -o teste_memoria teste_memoria.c
 * Executar com Valgrind:
 *   valgrind --leak-check=full --track-origins=yes ./teste_memoria
 * @return int
 */
int main(void) {
    printf("Iniciando teste Valgrind...\n");
    
    func_com_vazamento();
    func_uso_apos_free();
    
    // Acesso a memória não inicializada
    int *ptr2 = malloc(sizeof(int));
    printf("Valor não inicializado: %d\n", *ptr2);
    free(ptr2);
    
    printf("Fim do teste.\n");
    return 0;
}

/**
 * Exemplo de vazamento de memória
 * Aloca um vetor de inteiros e não libera a memória.
 * Isso deve ser detectado pelo Valgrind.
 * 
 * @return void
 */
void func_com_vazamento(void) {
    int *ptr = malloc(100 * sizeof(int));
    // Vazamento: falta free(ptr)
    printf("Alocou memória (%p)\n", (void *)ptr);
}

/**
 * Exemplo de uso após free
 * Aloca um inteiro, atribui valor, libera a memória e tenta usar o ponteiro novamente.
 * Isso é um erro e deve ser detectado pelo Valgrind.
 * Porém o gcc também detecta esse erro em tempo de compilação com -Wall -Wextra -pedantic
 * @return void
 */
void func_uso_apos_free(void) {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    *ptr = 100; // Uso após free!
}
