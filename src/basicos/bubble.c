#include "../algoritmos.h" //Deus nos dê forças para iniciar essa empreitada

/* Organizador de Bolhas(babousortis): Cria a função bubbleSort que recebe um vetor de inteiros v, o tamanho do vetor n e um ponteiro para a estrutura Metricas m. 
função implementa o algoritmo de ordenação Bubble Sort, que compara elementos adjacentes e os troca se estiverem na ordem errada,
repetindo esse processo até que o vetor esteja ordenado. 
Durante a execução, a função atualiza os contadores de comparações e trocas na estrutura Metricas.*/

void bubbleSort(int v[], int n, Metricas *m) {
    for (int i = 0; i < n - 1 ; i++){ //para i = 0, até i<n-1, some 1 a i  
        int trocou = 0; //variável para verificar se houve troca
        for (int j = 0; j < n-i-1; j++){ // para j=0 até j<n-1, some 1 a j
            m->comparacoes++;
            if (v[j] > v[j+1]) { // verifica se o elemeto atual é maior q o próximo na malemolencia
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                trocou = 1;
                m->trocas++;
            } //esqueci a chave antes kkjk
        }
        if (!trocou) // se não houve troca, o vetor está ordenado, one hundred percent
            break;
    }
}