#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Factura {
	int cod;
	int pret;
	int nrCeva;
	char* numeFactura;
	char* ceva;
};

struct Heap {
	Factura* elemente;
	int dim_maxima;
	int dim_efectiva;
};

struct BinaryTree {
	Factura info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};

/////////////////Cerinta-3////////////////////////////
void afisare_bin(Factura apel) {
	printf("\nCod: %d pret: %d  nrCeva: %d numeFactura: %s ceva: %s", apel.cod, apel.pret, apel.nrCeva, apel.numeFactura, apel.ceva);
}
void afisare_binuri(Factura* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_bin(apeluri[i]);
	}
}

BinaryTree* creare_nod(Factura apel, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nod = (BinaryTree*)malloc(sizeof(BinaryTree));
	nod->info = apel;
	nod->dreapta = dreapta;
	nod->stanga = stanga;
	return nod;
}

BinaryTree* inserare_nod(Factura apel, BinaryTree* radacina) {
	if (radacina) {
		if (radacina->info.pret > apel.pret) {
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
		afisare_bin(radacina->info);
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
	}
}
//Dezalocari
void dezalocare(BinaryTree*& radacina) {
	if (radacina) {
		dezalocare(radacina->dreapta);
		dezalocare(radacina->stanga);
		free(radacina);
		radacina = NULL;
	}
}
//////////////////////////////////////////


void afisare_apel_urgenta(Factura apel) {
	printf("\nCod: %d pret: %d  nrCeva: %d numeFactura: %s ceva: %s", apel.cod, apel.pret, apel.nrCeva, apel.numeFactura, apel.ceva);
}
void afisare_apeluri_urgenta(Factura* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_apel_urgenta(apeluri[i]);
	}
}
void interschimbare(Heap& heap, int max, int pozitie) {
	Factura aux = heap.elemente[max];
	heap.elemente[max] = heap.elemente[pozitie];
	heap.elemente[pozitie] = aux;
}

void filtrare(Heap& heap, int parinte) {
	int pozitieFiuStanga = 2 * parinte + 1;
	int pozitieFiuDreapta = 2 * parinte + 2;
	int max = parinte;
	if (pozitieFiuStanga < heap.dim_efectiva && heap.elemente[max].pret < heap.elemente[pozitieFiuStanga].pret) {
		max = pozitieFiuStanga;
	}
	if (pozitieFiuDreapta < heap.dim_efectiva &&
		heap.elemente[max].pret < heap.elemente[pozitieFiuDreapta].pret) {
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

void initializare_heap(Heap* heap, Factura elemente[], int numar_elemente, int dimensiune_maxima)
{
	heap->dim_maxima = dimensiune_maxima;
	heap->dim_efectiva = numar_elemente;
	heap->elemente = (Factura*)malloc(sizeof(Factura) * numar_elemente);
	for (int i = 0; i < numar_elemente; i++)
	{
		heap->elemente[i] = elemente[i];
	}
	for (int i = (heap->dim_efectiva - 1) / 2; i >= 0; i--)
	{
		filtrare(*heap, i);
	}
}

void inserare_heap(Heap& heap, Factura apel) {
	if (heap.dim_efectiva < heap.dim_maxima) {
		Factura* temp = (Factura*)malloc(sizeof(Factura) * (heap.dim_efectiva + 1));
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

void dezalocare_heap(Heap heap) {
	if (heap.dim_efectiva > 0 && heap.elemente != NULL) {
		free(heap.elemente);
	}
}


struct nod {
	Factura info;
	nod* next;
};

nod* inserare_element(nod*& cap, Factura info) {
	if (cap == NULL) {
		cap = (nod*)malloc(sizeof(nod));
		//cap->info = info;
		cap->info.cod = info.cod;
		cap->info.pret = info.pret;
		cap->info.nrCeva = info.nrCeva;
		cap->info.numeFactura = (char*)malloc(sizeof(char) * (strlen(info.numeFactura)));
		cap->info.ceva = (char*)malloc(sizeof(char) * (strlen(info.ceva)));
		strcpy(cap->info.numeFactura, info.numeFactura);
		strcpy(cap->info.ceva, info.ceva);
		cap->next = NULL;
	}
	else
	{
		nod* cursor = cap;
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->next = NULL;
		//nou->info = info;
		nou->info.nrCeva = info.nrCeva;
		nou->info.cod = info.cod;
		nou->info.pret = info.pret;
		nou->info.numeFactura = (char*)malloc(sizeof(char) * (strlen(info.numeFactura)));
		nou->info.ceva = (char*)malloc(sizeof(char) * (strlen(info.ceva)));
		strcpy(nou->info.numeFactura, info.numeFactura);
		strcpy(nou->info.ceva, info.ceva);
		cursor->next = nou;
	}
	return cap;
}
void creare_lista(BinaryTree* radacina, nod*& cap) {
	if (radacina == NULL) return;
	if (radacina->info.cod < 5) {
		inserare_element(cap, radacina->info);
	}

	creare_lista(radacina->stanga, cap);
	creare_lista(radacina->dreapta, cap);
}
void traversare(nod* cap) {
	printf("\nAfisare lista\n");
	nod* cursor;
	cursor = cap;
	while (cursor) {
		printf("\nCod: %d Pret: %d Nume: %s Categorie: %s", cursor->info.cod, cursor->info.pret, cursor->info.numeFactura, cursor->info.ceva);
		cursor = cursor->next;
	}
}

void dezalocarelista(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		nod* temp2 = temp->next;

		free(temp);
		temp = temp2;
	}
}
int main() {
	FILE* file = fopen("Factura.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Factura* facturi = (Factura*)malloc(sizeof(Factura) * nr);

	while (fgets(buffer, 128, file)) {
		Factura a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.pret = atoi(token);

		token = strtok(NULL, splitter);
		a.nrCeva = atoi(token);

		token = strtok(NULL, splitter);
		a.numeFactura = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.numeFactura, token);

		token = strtok(NULL, splitter);
		a.ceva = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.ceva, token);

		facturi[i++] = a;
	}
	printf("\n-------------------------- Cerinta-1 ----------------------------------------\n");
	Heap heap;
	initializare_heap(&heap, facturi, nr, 100);
	afisare_heap(heap);


	printf("\n-------------------------- Cerinta-3 ----------------------------------------\n");
		BinaryTree* radacina = NULL;
		for (int i = 0; i < nr; i++) {
			if(heap.elemente[i].pret<400)
			radacina = inserare_nod(heap.elemente[i], radacina);
		}
		afisare_preordine(radacina);

		printf("\n-------------------------- Cerinta-4 ----------------------------------------\n");
		nod* cap = NULL;
		creare_lista(radacina, cap);
		traversare(cap);

		//
		dezalocare(radacina);
		dezalocarelista(cap);
		dezalocare_heap(heap);

}