/* tests/test_basic.c */
#include <stdio.h>
#include <stdlib.h>
#include "../src/algoritmos.h"

typedef void (*SortFn)(int[], int, Metricas *);

static int falhas = 0;

static int estaOrdenado(const int v[], int n) {
    for (int i = 1; i < n; i++)
        if (v[i - 1] > v[i]) return 0;
    return 1;
}

static long soma(const int v[], int n) {
    long s = 0;
    for (int i = 0; i < n; i++) s += v[i];
    return s;
}

/* Ordena uma cópia de 'orig' e confere: (1) está ordenado e (2) não perdeu elementos */
static void verifica(const char *alg, const char *caso, SortFn fn, const int orig[], int n) {
    int *v = malloc((size_t)(n > 0 ? n : 1) * sizeof(int));
    if (v == NULL) { fprintf(stderr, "falta de memória\n"); exit(2); }
    for (int i = 0; i < n; i++) v[i] = orig[i];

    long antes = soma(v, n);
    Metricas m = {0, 0};
    fn(v, n, &m);

    int ok = estaOrdenado(v, n) && soma(v, n) == antes;
    printf("%-7s  %-10s %s\n", ok ? "PASSOU" : "FALHOU", alg, caso);
    if (!ok) falhas++;
    free(v);
}

static void testaAlgoritmo(const char *nome, SortFn fn) {
    int aleatorio[]   = {5, 1, 4, 2, 8};
    int ordenado[]    = {1, 2, 3, 4, 5, 6};
    int invertido[]   = {6, 5, 4, 3, 2, 1};
    int duplicatas[]  = {3, 1, 3, 2, 1, 3, 2};
    int negativos[]   = {0, -5, 7, -1, 3};
    int unico[]       = {42};
    int vazio[1]      = {0};

    verifica(nome, "aleatório",  fn, aleatorio,  5);
    verifica(nome, "ordenado",   fn, ordenado,   6);
    verifica(nome, "invertido",  fn, invertido,  6);
    verifica(nome, "duplicatas", fn, duplicatas, 7);
    verifica(nome, "negativos",  fn, negativos,  5);
    verifica(nome, "n=1",        fn, unico,      1);
    verifica(nome, "n=0",        fn, vazio,      0);
}

/* Confere as comparações e trocas/movimentações esperadas para um vetor conhecido */
static void testaMetricas(const char *alg, const char *caso, SortFn fn,
                          const int orig[], int n, unsigned long comp, unsigned long mov) {
    int *v = malloc((size_t)n * sizeof(int));
    if (v == NULL) { fprintf(stderr, "falta de memória\n"); exit(2); }
    for (int i = 0; i < n; i++) v[i] = orig[i];

    Metricas m = {0, 0};
    fn(v, n, &m);

    int ok = (m.comparacoes == comp && m.trocas == mov);
    printf("%-7s  %-10s métricas %s\n", ok ? "PASSOU" : "FALHOU", alg, caso);
    if (!ok) {
        printf("         esperado comp=%lu mov=%lu, obtido comp=%lu mov=%lu\n",
               comp, mov, m.comparacoes, m.trocas);
        falhas++;
    }
    free(v);
}

int main(void) {
    int base[]     = {5, 1, 4, 2, 8};
    int ordenado[] = {1, 2, 3, 4, 5};

    testaAlgoritmo("bubble", bubbleSort);
    testaMetricas("bubble", "{5,1,4,2,8}", bubbleSort, base, 5, 9, 4);
    testaMetricas("bubble", "ordenado", bubbleSort, ordenado, 5, 4, 0);
    /* TODO: adicione aqui as chamadas dos demais algoritmos, à medida que os implementar */

    if (falhas > 0) {
        printf("\n%d teste(s) falharam\n", falhas);
        return 1;               /* código de saída != 0: o make test também falha */
    }
    printf("\nTodos os testes passaram\n");
    return 0;
}
