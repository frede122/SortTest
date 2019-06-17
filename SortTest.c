#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ordenar.h"

int SIZE;

void gravarArquivoInt(char *, int *, int);
void gravarArquivoTexto(char *, char *);
void printVetor(int *);
void tempoBubble(int [], char [8][30], int);
void tempoMerge(int [], char [8][30], int);
void tempoQuickSort(int [], char [1][30], int);
void tempoSelection(int [], char [8][30], int);
void tempoInsertion(int [], char [8][30], int);
void tempoHeapSort(int [], char [8][30], int);
void tempoRadixSort(int [], char [8][30], int);



int main() {

    int tam[]={	
				100000, 
				200000, 
				400000, 
				800000, 
				100000, 
				200000, 
				400000, 
				800000
	};
    char vetorArquivo[][30]={
								"vetor_aleatorio_100000", 
								"vetor_aleatorio_200000", 
								"vetor_aleatorio_400000", 
								"vetor_aleatorio_800000",
								"vetor_inverso_100000",
								"vetor_inverso_200000", 
								"vetor_inverso_400000", 
								"vetor_inverso_800000"
	};
	FILE *saida;
	saida = fopen("saida.csv", "w");
	fprintf(saida, "Algoritimo;Lista;Tempo\n;;\n");
	fclose(saida);
							
	//tempoRadixSort(tam, vetorArquivo);
    //tempoHeapSort(tam, vetorArquivo);
    //tempoMerge(tam, vetorArquivo, 8);
    tempoQuickSort(tam, vetorArquivo, 8);
    //tempoSelection(tam, vetorArquivo);gcc
    //tempoInsertion(tam, vetorArquivo);
	//tempoBubble(tam, vetorArquivo);

    return 0;
}


void gravarArquivoInt(char *nomeDoArquivo, int *v, int tam){
  FILE *pont_arq;
  pont_arq = fopen(nomeDoArquivo, "a");
  int i;
  for(i=0; i< tam; i++)
  	fprintf(pont_arq, "%d ", v[i]);
  fclose(pont_arq);
}

void gravarArquivoTexto(char *nomeDoArquivo, char *v){
  FILE *pont_arq;
  pont_arq = fopen(nomeDoArquivo, "a");
  fprintf(pont_arq, "%s\n", v);
  fclose(pont_arq);	
}

void printVetor(int *vetor) {
    int i;

    printf("\n");
    for(i=0; i<SIZE; i++) {
        printf("%d ", vetor[i]);
    }
}

void carregarVetor(int *vetor, char *filename, int SIZE) {
    FILE *arquivo;
    int i=0;

    arquivo = fopen(filename, "r");

    for(i=0; i<SIZE; i++) {
        fscanf(arquivo, "%d", &vetor[i]);
    }

    fclose(arquivo);
}

void tempoBubble(int tam[], char vetorArquivo[8][30], int qtd){
    int i;
    for(i = 0; i < qtd; i++){
        clock_t start, end;
        double cpu_time_used;
        SIZE = tam[i];
        //int vet[tam[i]];
        int *vet = (int*)malloc(sizeof(int)* SIZE);
        carregarVetor(vet, vetorArquivo[i], SIZE);
        printVetor(vet); 
        printf("\n\nExecutando a ordenacao...\n");
        start = clock();
        ordenarBolha(vet, SIZE);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printVetor(vet);
        printf("\n\nO tempo gasto foi %.6f segundos\n\n", cpu_time_used);
        char saida[50];
        sprintf(saida, "Bubble;%s;%.6f S.", vetorArquivo[i], cpu_time_used);       
        gravarArquivoTexto("saida.csv", saida);
        char tex[30];
        sprintf(tex, "saidas/Bubble %s", vetorArquivo[i]);
        gravarArquivoInt(tex, vet, SIZE);
        free(vet);
    }
    gravarArquivoTexto("saida.csv", "\n\n");
}

void tempoMerge(int tam[], char vetorArquivo[8][30], int qtd){
    int i;
    for(i = 0; i < qtd; i++){
        clock_t start, end;
        double cpu_time_used;
        SIZE = tam[i];
        int *vet = (int*)malloc(sizeof(int)* tam[i]);
        //int vet[tam[i]];
        carregarVetor(vet, vetorArquivo[i], tam[i]);
        printVetor(vet);
        printf("\n\nExecutando a ordenacao...\n");
        start = clock();  
        merge(0, tam[i],vet);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printVetor(vet);
        printf("\n\nO tempo gasto foi %.6f segundos\n\n", cpu_time_used);
        char saida[50];
        sprintf(saida, "Merge;%s;%.6f S.", vetorArquivo[i], cpu_time_used);       
        gravarArquivoTexto("saida.csv", saida);
        free(vet);
    }
 	gravarArquivoTexto("saida.csv", "\n\n");
}

void tempoQuickSort(int tam[], char vetorArquivo[8][30], int qtd){
    int i;
    for(i = 0; i < qtd; i++){
        clock_t start, end;
        double cpu_time_used;
        SIZE = tam[i];
        int *vet = (int*)malloc(sizeof(int)* SIZE);
        carregarVetor(vet, vetorArquivo[i], tam[i]);
        //printVetor(vet);
        printf("\n\nExecutando a ordenacao Quicksort %s...\n", vetorArquivo[i]);
        start = clock();  
		quick(vet, 0, tam[i] - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        //printVetor(vet);
        printf("\n\nO tempo gasto foi %.6f segundos\n\n", cpu_time_used);
        char saida[50];
        sprintf(saida, "QuickSort;%s;%.6f S.", vetorArquivo[i], cpu_time_used);       
        gravarArquivoTexto("saida.csv", saida);
        char tex[40];
        sprintf(tex, "saidas\\QuickSort%s", vetorArquivo[i]);
        gravarArquivoInt(tex, vet, SIZE);
        free(vet);
    }
      
    gravarArquivoTexto("saida.csv", "\n\n");
}

void tempoSelection(int tam[], char vetorArquivo[8][30], int qtd){
    int i;
    for(i = 0; i < qtd; i++){
        clock_t start, end;
        double cpu_time_used;
        SIZE = tam[i];
        int *vet = (int*)malloc(sizeof(int) * SIZE);
        carregarVetor(vet, vetorArquivo[i], tam[i]);
        printVetor(vet);
        printf("\n\nExecutando a ordenacao ...\n");
        start = clock();
		ordenarSelection(vet, SIZE);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printVetor(vet);
        printf("\n\nO tempo gasto foi %.6f segundos\n\n", cpu_time_used);
        char saida[50];
        sprintf(saida, "Selection;%s;%.6f S.", vetorArquivo[i], cpu_time_used);       
        gravarArquivoTexto("saida.csv", saida);
        free(vet);
    }
    gravarArquivoTexto("saida.csv", "\n\n");
}

void tempoInsertion(int tam[], char vetorArquivo[8][30], int qtd){
    int i;
    for(i = 0; i < qtd; i++){
        clock_t start, end;
        double cpu_time_used;
        SIZE = tam[i];
        int *vet = (int*)malloc(sizeof(int) * SIZE);
        carregarVetor(vet, vetorArquivo[i], tam[i]);
        printVetor(vet);
        printf("\n\nExecutando a ordenacao...\n");
        start = clock();
        ordenarInsertion(vet, SIZE);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printVetor(vet);
        printf("\n\nO tempo gasto foi %.6f segundos\n\n", cpu_time_used);
        char saida[50];
        sprintf(saida, "Insertion;%s;%.6f S.", vetorArquivo[i], cpu_time_used);       
        gravarArquivoTexto("saida.csv", saida);
        free(vet);
    }   
	gravarArquivoTexto("saida.csv", "\n\n");
}

void tempoHeapSort(int tam[], char vetorArquivo[8][30], int qtd){
    int i;
    for(i = 0; i < qtd; i++){
        clock_t start, end;
        double cpu_time_used;
        SIZE = tam[i];
        int *vet = (int*)malloc(sizeof(int)* SIZE);
        carregarVetor(vet, vetorArquivo[i], tam[i]);
        printVetor(vet);
        printf("\n\nExecutando a ordenacao...\n");
        start = clock();
        ordenarHeap(vet, SIZE);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printVetor(vet);
        printf("\n\nO tempo gasto foi %.6f segundos\n\n", cpu_time_used);
        char saida[50];
        sprintf(saida, "HeapSort;%s;%.6f S.", vetorArquivo[i], cpu_time_used);       
        gravarArquivoTexto("saida.csv", saida);
        free(vet);
    }   
	gravarArquivoTexto("saida.csv", "\n\n");
}

void tempoRadixSort(int tam[], char vetorArquivo[8][30], int qtd){
    int i;
    for(i = 0; i < qtd; i++){
        clock_t start, end;
        double cpu_time_used;
        SIZE = tam[i];
        int *vet = (int*)malloc(sizeof(int)* SIZE);
        carregarVetor(vet, vetorArquivo[i], tam[i]);
        printVetor(vet);
        printf("\n\nExecutando a ordenacao...\n");
        start = clock();
        ordenarRadix(vet,SIZE);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printVetor(vet);
        printf("\n\nO tempo gasto foi %.6f segundos\n\n", cpu_time_used);
        char saida[50];
        sprintf(saida, "RadixSort;%s;%.6f S.", vetorArquivo[i], cpu_time_used);       
        gravarArquivoTexto("saida.csv", saida);
        free(vet);
    }   
	gravarArquivoTexto("saida.csv", "\n\n");
}

