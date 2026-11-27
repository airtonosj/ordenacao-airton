//Procurar o menor de todos os elementos do vetor, e levar para a primeira posição, 
//depois procurar o segundo menor e levar para a segunda posição, e assim por diante, até que o vetor esteja ordenado.
#include "../algoritmos.h" //Deus nos dê forças para iniciar essa empreitada

void selectionSort(int v[], int n, Metricas *m) {
    for (int i = 0; i < n - 1; i++) { //para i = 0, até i<n-1, some 1 a i
        int minIndex = i; // assume que o menor elemento é o primeiro da sublista não ordenada
        for (int j = i + 1; j < n; j++) { // para j=i+1 até j<n, some 1 a j
            m->comparacoes++;
            if (v[j] < v[minIndex]) { // verifica se o elemento atual é menor que o menor encontrado
                minIndex = j; // atualiza o índice do menor elemento
            }
        }
        if (minIndex != i) { // se o menor elemento não estiver na posição correta, troca de posição
            int aux = v[i];
            v[i] = v[minIndex];
            v[minIndex] = aux;
            m->trocas++;
        }
    }
}// lembrar de atualizar o main do test/test_basic 