/* src/basicos/bubble.c */
#include "../algoritmos.h"

void bubbleSort(int v[], int n, Metricas *m) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        /* a cada passada, os i últimos elementos já estão no lugar */
        for (int j = 0; j < n - 1 - i; j++) {
            m->comparacoes++;                 /* compara dois valores do vetor */
            if (v[j] > v[j + 1]) {
                int aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
                m->trocas++;                  /* troca de dois elementos */
                trocou = 1;
            }
        }
        if (!trocou)                          /* passada sem trocas: já ordenado */
            break;
    }
}
