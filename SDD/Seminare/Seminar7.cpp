
#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct ApelUrgenta {
	int cod;
	int prioritate;
	char adresa[100];
};

struct Heap {
	ApelUrgenta* elemente;
	int dim_maxima;
	int dim_efectiva;
};

//==================================== GESTIONARE FISIER =========================================

ApelUrgenta citire_apel_urgenta_fisier(FILE* fisier) {
	ApelUrgenta apel;
	fscanf_s(fisier, "%d", &apel.cod);
	fscanf_s(fisier, "%d", &apel.prioritate);
	fgetc(fisier);//fflush
	fgets(apel.adresa, 100, fisier);
	strtok(apel.adresa, "\n");
	return apel;
}

ApelUrgenta citire_apel_urgenta_consola() {
	ApelUrgenta apel;
	printf("\nCod: ");
	scanf_s("%d", &apel.cod);
	printf("\nPrioritate: ");
	scanf_s("%d", &apel.prioritate);
	getc(stdin);
	printf("\nAdresa: ");
	gets_s(apel.adresa, 100);
	return apel;
}

void afisare_apel_urgenta(ApelUrgenta apel) {
	printf("\nCod: %d Prioritate: %d Adresa: %s", apel.cod, apel.prioritate, apel.adresa);
}

ApelUrgenta* citire_apeluri_urgenta_fisier(int &nr) {
	ApelUrgenta* apeluri = NULL;
	FILE* fisier;
	fopen_s(&fisier, "apeluri_urgenta.txt", "r");
	if (fisier != NULL) {
		fscanf_s(fisier, "%d", &nr);
		apeluri = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*nr);
		for (int i = 0; i < nr; i++) {
			apeluri[i] = citire_apel_urgenta_fisier(fisier);
		}
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu s-a putut deschide");
	}
	return apeluri;
}

void afisare_apeluri_urgenta(ApelUrgenta* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_apel_urgenta(apeluri[i]);
	}
}

//================================ METODE HEAP ========================================

void interschimbare(Heap &heap, int max, int pozitie) {
	ApelUrgenta aux = heap.elemente[max];
	heap.elemente[max] = heap.elemente[pozitie];
	heap.elemente[pozitie] = aux;
}

void filtrare(Heap &heap, int parinte) {
	int pozitieFiuStanga = 2 * parinte + 1;
	int pozitieFiuDreapta = 2 * parinte + 2;
	int max = parinte;
	if (pozitieFiuStanga < heap.dim_efectiva && heap.elemente[max].prioritate < heap.elemente[pozitieFiuStanga].prioritate) {
		max = pozitieFiuStanga;
	}
	if (pozitieFiuDreapta < heap.dim_efectiva &&
		heap.elemente[max].prioritate < heap.elemente[pozitieFiuDreapta].prioritate) {
		max = pozitieFiuDreapta;
	}
	if (max != parinte) {
		interschimbare(heap, max, parinte);
		filtrare(heap, max);
	}
}

void afisare_heap(Heap heap) {
	for (int i = 0; i < heap.dim_efectiva; i++) {
		afisare_apel_urgenta(heap.elemente[i]);
	}
}

void initializare_heap(Heap *heap, ApelUrgenta elemente[], int numar_elemente, int dimensiune_maxima)
{
	heap->dim_maxima = dimensiune_maxima;
	heap->dim_efectiva = numar_elemente;
	heap->elemente = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*numar_elemente);
	for (int i = 0; i < numar_elemente; i++)
	{
		heap->elemente[i] = elemente[i];
	}
	for (int i = (heap->dim_efectiva - 1) / 2; i >= 0; i--)
	{
		filtrare(*heap, i);
	}
}

void inserare_heap(Heap &heap, ApelUrgenta apel) {
	if (heap.dim_efectiva < heap.dim_maxima) {
		ApelUrgenta* temp = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*(heap.dim_efectiva + 1));
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
			&& heap.elemente[indexFiu].prioritate > heap.elemente[indexParinte].prioritate) {
			interschimbare(heap, indexFiu, indexParinte);
			indexFiu = indexParinte;
			indexParinte = (indexFiu - 1) / 2;
		}
	}
	else {
		printf("\nNu mai este loc disponibil in heap");
	}
}

ApelUrgenta extragere_heap(Heap &heap) {
	if (heap.dim_efectiva > 0) {
		ApelUrgenta apel = heap.elemente[0];
		ApelUrgenta* temp = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*(heap.dim_efectiva - 1));
		for (int i = 1; i < heap.dim_efectiva; i++) {
			temp[i - 1] = heap.elemente[i];
		}
		free(heap.elemente);
		heap.elemente = temp;
		heap.dim_efectiva--;
		for (int i = (heap.dim_efectiva - 1) / 2; i >= 0; i--) {
			filtrare(heap, i);
		}
		return apel;
	}
	else {
		printf("\nNu mai exista elemente in heap");
	}
}

void dezalocare_heap(Heap heap) {
	if (heap.dim_efectiva > 0 && heap.elemente != NULL) {
		free(heap.elemente);
	}
}

void main() {
	int nr;
	ApelUrgenta* apeluri = citire_apeluri_urgenta_fisier(nr);
	afisare_apeluri_urgenta(apeluri, nr);
	printf("\n-------------------------- Alocare Heap ----------------------------------------\n");
	Heap heap;
	initializare_heap(&heap, apeluri, nr, 100);
	afisare_heap(heap);
	printf("\n-------------------------- Inserare Heap ----------------------------------------\n");
	int ok = 1;
	while (ok == 1) {
		ApelUrgenta apelNou = citire_apel_urgenta_consola();
		inserare_heap(heap, apelNou);
		printf("\nDoriti sa mai adaugati apeluri? Da-1/Nu-0");
		scanf_s("%d", &ok);
	}
	afisare_heap(heap);
	printf("\n-------------------------- Extragere Heap ----------------------------------------\n");
	ApelUrgenta extrax = extragere_heap(heap);
	afisare_heap(heap);
	dezalocare_heap(heap);
}