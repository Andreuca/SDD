
#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Platforma {
	int cod;
	int pret;
	int garantie;
	char* numePlatforma;
	char* numeProvider;
};

struct Heap {
	Platforma* elemente;
	int dim_maxima;
	int dim_efectiva;
};
void afisare_platforma(Platforma apel) {
	printf("\nCod: %d pret: %d  garantie: %d numePlatforma: %s numeProvider: %s", apel.cod, apel.pret, apel.garantie, apel.numePlatforma, apel.numeProvider);
}
void afisare_platforme(Platforma* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_platforma(apeluri[i]);
	}
}
void interschimbare(Heap& heap, int max, int pozitie) {
	Platforma aux = heap.elemente[max];
	heap.elemente[max] = heap.elemente[pozitie];
	heap.elemente[pozitie] = aux;
}

void filtrare(Heap& heap, int parinte) {
	int pozitieFiuStanga = 2 * parinte + 1;
	int pozitieFiuDreapta = 2 * parinte + 2;
	int max = parinte;
	if (pozitieFiuStanga < heap.dim_efectiva && heap.elemente[max].pret > heap.elemente[pozitieFiuStanga].pret) {
		max = pozitieFiuStanga;
	}
	if (pozitieFiuDreapta < heap.dim_efectiva && heap.elemente[max].pret > heap.elemente[pozitieFiuDreapta].pret) {
		max = pozitieFiuDreapta;
	}
	if (max != parinte) {
		interschimbare(heap, max, parinte);
		filtrare(heap, max);
	}
}

void afisare_heap(Heap heap) {
	for (int i = 0; i < heap.dim_efectiva; i++) {
		afisare_platforma(heap.elemente[i]);
	}
}

void initializare_heap(Heap* heap, Platforma elemente[], int numar_elemente, int dimensiune_maxima)
{
	heap->dim_maxima = dimensiune_maxima;
	heap->dim_efectiva = numar_elemente;
	heap->elemente = (Platforma*)malloc(sizeof(Platforma) * numar_elemente);
	for (int i = 0; i < numar_elemente; i++)
	{
		heap->elemente[i] = elemente[i];
	}
	for (int i = (heap->dim_efectiva - 1) / 2; i >= 0; i--)
	{
		filtrare(*heap, i);
	}
}

void inserare_heap(Heap& heap, Platforma apel) {
	if (heap.dim_efectiva < heap.dim_maxima) {
		Platforma* temp = (Platforma*)malloc(sizeof(Platforma) * (heap.dim_efectiva + 1));
		for (int i = 0; i < heap.dim_efectiva; i++) {
			temp[i] = heap.elemente[i];
		}
		temp[heap.dim_efectiva] = apel;
		free(heap.elemente);
		heap.dim_efectiva++;
		heap.elemente = temp;
		int indexFiu = heap.dim_efectiva - 1;
		int indexParinte = (indexFiu - 1) / 2;
		while (indexParinte >= 0
			&& heap.elemente[indexFiu].pret > heap.elemente[indexParinte].pret) {
			interschimbare(heap, indexFiu, indexParinte);
			indexFiu = indexParinte;
			indexParinte = (indexFiu - 1) / 2;
		}
	}
	else {
		printf("\nNu mai este loc disponibil in heap");
	}
}

Platforma extragere_heap(Heap& heap) {
	if (heap.dim_efectiva > 0) {
		Platforma apel = heap.elemente[0];
		Platforma* temp = (Platforma*)malloc(sizeof(Platforma) * (heap.dim_efectiva - 1));
		for (int i = 1; i < heap.dim_efectiva; i++) {
			temp[i - 1] = heap.elemente[i];
		}
		free(heap.elemente);
		heap.elemente = temp;
		heap.dim_efectiva--;
		for (int i = (heap.dim_efectiva - 1) / 2; i >= 0; i--) {
			filtrare(heap, i);
		}
		apel.pret++;
		return apel;
	}
	else {
		printf("\nNu mai exista elemente in heap");
	}
}
/////////////////////////////////// Cerinta-3//////////////////////////////////

struct BinaryTree {
	Platforma info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};
BinaryTree* creare_nod(Platforma apel, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nod = (BinaryTree*)malloc(sizeof(BinaryTree));
	nod->info.cod = apel.cod;
	nod->info.pret = apel.pret;
	nod->info.garantie = apel.garantie;
	nod->info.numePlatforma = (char*)malloc(sizeof(char)*(strlen(apel.numePlatforma)));
	nod->info.numeProvider = (char*)malloc(sizeof(char) * (strlen(apel.numeProvider)));
	strcpy(nod->info.numePlatforma, apel.numePlatforma);
	strcpy(nod->info.numeProvider, apel.numeProvider);
	nod->dreapta = dreapta;
	nod->stanga = stanga;
	return nod;
}
BinaryTree* inserare_nod(Platforma apel, BinaryTree* radacina) {
	if (radacina) {
		if (radacina->info.cod > apel.cod) {
			radacina->stanga = inserare_nod(apel, radacina->stanga);
		}
		else {
			radacina->dreapta = inserare_nod(apel, radacina->dreapta);
		}
		return radacina;
	}
	else {
		return creare_nod(apel, NULL, NULL);
	}
}
void afisare_preordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_platforma(radacina->info);
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
	}
}

///////////////////////////////////////////////////////
void afisare_ramurici(BinaryTree* radacina) {
	if (radacina) {
		if (radacina->dreapta == NULL || radacina->stanga == NULL) {
			if (radacina->dreapta != NULL || radacina->stanga != NULL) {
				afisare_platforma(radacina->info);
			}
		}
		afisare_ramurici(radacina->stanga);
		afisare_ramurici(radacina->dreapta);
	}
}
void dezalocareBtree(BinaryTree*& radacina) {
	if (radacina) {
		dezalocareBtree(radacina->dreapta);
		dezalocareBtree(radacina->stanga);
		free(radacina);
		radacina = NULL;
	}
}
void dezalocare_heap(Heap heap) {
	if (heap.dim_efectiva > 0 && heap.elemente != NULL) {
		free(heap.elemente);
	}
}
int main() {
	FILE* file = fopen("platforme.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Platforma* platforme = (Platforma*)malloc(sizeof(Platforma) * nr);

	while (fgets(buffer, 128, file)) {
		Platforma a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.pret = atoi(token);

		token = strtok(NULL, splitter);
		a.garantie = atoi(token);

		token = strtok(NULL, splitter);
		a.numePlatforma = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.numePlatforma, token);

		token = strtok(NULL, splitter);
		a.numeProvider = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.numeProvider, token);

		platforme[i++] = a;
	}
	printf("\n-------------------------- Cerinta-1 ----------------------------------------\n");
	Heap heap;
	initializare_heap(&heap, platforme, nr, 100);
	afisare_heap(heap);
	printf("\n-------------------------- Cerinta-2 ----------------------------------------\n");
	Platforma a = extragere_heap(heap);
	inserare_heap(heap, a);
	afisare_heap(heap);
	printf("\n-------------------------- Cerinta-3 ----------------------------------------\n");
	BinaryTree* radacina = NULL;
	int n;
	printf("Primele n elemente:");
	scanf("%d", &n);
	printf("\n");
	if (n <= nr) {
		for (int i = 0; i < n; i++) {
		radacina = inserare_nod(heap.elemente[i], radacina);
		}
	}
	afisare_preordine(radacina);
	printf("\n-------------------------- Cerinta-4 ----------------------------------------\n");
	afisare_ramurici(radacina);
	dezalocare_heap(heap);
	dezalocareBtree(radacina);
}


