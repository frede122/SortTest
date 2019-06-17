void troca(int *a, int *);
void ordenarBolha(int *, int);
void intercala(int , int , int , int []);
void merge(int , int , int []);
void ordenarSelection(int *, int);
void ordenarInsertion(int *, int);
int separa(int [], int , int );
void quicksort(int [], int , int ); 
void peneira(int *, int , int );
void ordenarHeap(int *, int );
void ordenarRadix(int [], int);
void carregarVetor(int *, char *, int);
void quick(int *, int, int);

void troca(int *a, int *b) {
    int temp;
    temp = *a;
    *a  = *b;
    *b = temp;
}

//Bolha inicio
void ordenarBolha(int *vetor, int SIZE) {
    int i, j;

    for(i=0; i<SIZE-1; i++) {
        for(j=0; j<SIZE; j++) {
            if(vetor[j] > vetor[j+1]) {
                troca(&vetor[j], &vetor[j+1]);
            }
        }        
    }
}
// fim Bolha

//inicio Merge 
void intercala(int p, int q, int r, int v[]) {
    int *w;
    w = (int*) malloc( (r-p) * sizeof(int));
    int i=p;
    int j=q;
    int k=0;
    
    while(i<q && j<r) {
        if(v[i] <= v[j])
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }

    while(i<q)
        w[k++] = v[i++];

    while(j<r)
        w[k++] = v[j++];

    for(i=p; i<r; ++i)
        v[i] = w[i-p];

    free(w);
}

void merge(int p, int r, int v[]) {

    int q;
    if(p<r-1) {
        q = (p+r)/2;
        merge(p, q, v);
        merge(q, r, v);
        intercala(p, q, r, v);
    }
}
//fim merge

// inicio selection
void ordenarSelection(int *v, int SIZE) {
    int i, j, minIdx;

    for(i=0; i<SIZE-1; i++) {
        minIdx = i;
        //printf("\nPassada i: %d", i);

        for(j=i+1; j<SIZE-1; j++) {
            if(v[minIdx] > v[j]) 
                minIdx = j;
        }

        troca(&v[minIdx], &v[i]);
        //printVetor(v);
    }
}
// fim selection

// inicio insertion
void ordenarInsertion(int *v, int SIZE) {
    int i, j, chave;

    for(i=1; i<SIZE; i++) {
        //printf("\nPassada i: %d", i);
        chave = v[i];
        j = i-1;
        //printVetor(v);
        while(j>=0 && v[j] > chave) {
            v[j+1] = v[j];
            j--;
            //printVetor(v);
        }
        v[j+1] = chave;
        //printVetor(v);
    }
}

//fim insertion

// inicio quicksort
int separa(int v[], int p, int r) {
    int c=v[r];
    int t,k;
    int j=p;

    for(k=p; k<r; ++k) {
        if(v[k] <= c) {
            t=v[j];
            v[j] = v[k];
            v[k] = t;
            ++j;
        }
    }
    t=v[j];
    v[j] = v[r];
    v[r] = t;
    return j;
}


void quicksort(int v[], int p, int r) {
    int j;
    if(p<r) {
        j=separa(v, p, r);
        quicksort(v, p, j-1);
        quicksort(v, j+1, r);
    }
}




void quick(int *a, int left, int right) {
    int i, j, x, y;
     
    i = left;
    j = right;
    x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick(a, left, j);
    }
    if(i < right) {
        quick(a, i, right);
    }
}





//fim quicksort

// HeapSort inicio


void peneira(int *vet, int raiz, int fundo) {
	int pronto, filhoMax, tmp;

	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
		if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
		}
		else if (vet[raiz * 2] > vet[raiz * 2 + 1]) {
			filhoMax = raiz * 2;
		}
		else {
			filhoMax = raiz * 2 + 1;
		}

	if (vet[raiz] < vet[filhoMax]) {
		tmp = vet[raiz];
		vet[raiz] = vet[filhoMax];
		vet[filhoMax] = tmp;
		raiz = filhoMax;
    }
	else {
      pronto = 1;
	}
  }
}

void ordenarHeap(int *vet, int n) {
	int i, tmp;

	for (i = (n / 2); i >= 0; i--) {
		peneira(vet, i, n - 1);
	}

	for (i = n-1; i >= 1; i--) {
		tmp = vet[0];
		vet[0] = vet[i];
		vet[i] = tmp;
		peneira(vet, 0, i-1);
	}
}

// fim heapsort


// inicio do radixsort
 

void ordenarRadix(int vetor[], int tamanho) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));

    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }

    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }

    free(b);
}