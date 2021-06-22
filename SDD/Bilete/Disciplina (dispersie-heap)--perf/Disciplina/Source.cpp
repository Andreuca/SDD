#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include<stdio.h>
#include<stdlib.h>

struct Disciplina {
	int cod;
	int nrDisciplina;
	int nota;
	char* nume;
	char* prenume;
};
struct NodGradinita {
	Disciplina info;
	NodGradinita* next;
};

struct HashGradinita {
	int dimensiune;
	NodGradinita** elemente;
};

struct Heap {
	Disciplina* elemente;
	int dim_maxima;
	int dim_efectiva;
};

//////////////////////////Cerinta-3////////////////////////////
void afisare_apel_urgenta(Disciplina apel) {
	printf("\n%d %d %d %s %s", apel.cod, apel.nrDisciplina, apel.nota, apel.nume, apel.prenume);
}
void afisare_apeluri_urgenta(Disciplina* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_apel_urgenta(apeluri[i]);
	}
}
void interschimbare(Heap& heap, int max, int pozitie) {
	Disciplina aux = heap.elemente[max];
	heap.elemente[max] = heap.elemente[pozitie];
	heap.elemente[pozitie] = aux;
}
void filtrare(Heap& heap, int parinte) {
	int pozitieFiuStanga = 2 * parinte + 1;
	int pozitieFiuDreapta = 2 * parinte + 2;
	int max = parinte;
	if (pozitieFiuStanga < heap.dim_efectiva && heap.elemente[max].nota < heap.elemente[pozitieFiuStanga].nota) {
		max = pozitieFiuStanga;
	}
	if (pozitieFiuDreapta < heap.dim_efectiva &&
		heap.elemente[max].nota < heap.elemente[pozitieFiuDreapta].nota) {
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

void initializare_heap(Heap* heap, HashGradinita hs, int numar_elemente, int dimensiune_maxima)
{
	heap->dim_maxima = dimensiune_maxima;
	heap->dim_efectiva = numar_elemente;
	heap->elemente = (Disciplina*)malloc(sizeof(Disciplina) * numar_elemente);
	int j = 0;
	for (int i = 0; i < hs.dimensiune; i++)
	{
		if (hs.elemente[i] != NULL) {
		heap->elemente[j] = hs.elemente[i]->info;
		j++;
		}
	}
	for (int i = (heap->dim_efectiva - 1) / 2; i >= 0; i--)
	{
		filtrare(*heap, i);
	}
}

void inserare_heap(Heap& heap, Disciplina apel) {
	if (heap.dim_efectiva < heap.dim_maxima) {
		Disciplina* temp = (Disciplina*)malloc(sizeof(Disciplina) * (heap.dim_efectiva + 1));
		for (int i = 0; i < heap.dim_efectiva; i++) {
			temp[i] = heap.elemente[i];
		}

		///////////////////////////////////
		temp[heap.dim_efectiva].cod = apel.cod;
		temp[heap.dim_efectiva].nrDisciplina= apel.nrDisciplina;
		temp[heap.dim_efectiva].nota = apel.nota;
		temp[heap.dim_efectiva].nume = (char*)malloc(sizeof(char) * (strlen(apel.nume)));
		strcpy(temp[heap.dim_efectiva].nume, apel.nume);
		temp[heap.dim_efectiva].prenume = (char*)malloc(sizeof(char) * (strlen(apel.prenume)));
		strcpy(temp[heap.dim_efectiva].prenume, apel.prenume);
		/////////////////////////////////////

		free(heap.elemente);
		heap.dim_efectiva++;
		heap.elemente = temp;
		int indexFiu = heap.dim_efectiva - 1;
		int indexParinte = (indexFiu - 1) / 2;
		while (indexParinte >= 0
			&& heap.elemente[indexFiu].nota > heap.elemente[indexParinte].nota) {
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void afisare_student(Disciplina s) {
	printf("\n%d %d %d %s %s", s.cod, s.nrDisciplina, s.nota, s.nume, s.prenume);
}


int cod_hash(int cheie, HashGradinita hs) {
	return cheie % hs.dimensiune;
}

HashGradinita alocare_memorie() {
	HashGradinita hs;
	printf("\nIntroduceti dimensiunea hash: ");
	scanf_s("%d", &hs.dimensiune);
	hs.elemente = (NodGradinita**)malloc(sizeof(NodGradinita) * hs.dimensiune);
	for (int i = 0; i < hs.dimensiune; i++) {
		hs.elemente[i] = NULL;
	}
	return hs;
}


void inserare(Disciplina d, HashGradinita& hs) {
	if (hs.dimensiune != 0) {
	
		int hash = cod_hash(d.cod, hs); 
		while (hs.elemente[hash] != NULL) {
			hash = hash + 1;
			
		}
		if (hash < hs.dimensiune) {
			hs.elemente[hash] = (NodGradinita*)malloc(sizeof(NodGradinita));
			hs.elemente[hash]->next = NULL;
			hs.elemente[hash]->info = d;
		}
		else
			printf("Elementul cu codul %d nu poate fi inserat", d.cod);
	}
	else
	{
		printf("Dimensiune invalida");
	}
}
void adaugare_studenti_hash(HashGradinita& hs, int& nr, Disciplina* disci) {
	for (int i = 0; i < nr; i++)
	{
		Disciplina s = disci[i];
		inserare(s, hs);
	}
}
//Dezalocari
void dezalocare_lista(NodGradinita* cap) {

	if (cap != NULL) {
		NodGradinita* sters;
		while (cap != NULL) {
			sters = cap;
			cap = cap->next;
			free(sters);
		}
	}
}
void dezalocare_memorie(HashGradinita hs) {

	if (hs.dimensiune > 0 && hs.elemente != NULL) {
		for (int i = 0; i < hs.dimensiune; i++) {

			dezalocare_lista(hs.elemente[i]);
		}
		free(hs.elemente);
		hs.dimensiune = 0;
	}
}


void afisare_lista(NodGradinita* cap) {
	if (cap != NULL) {
		NodGradinita* cursor = cap;
		while (cursor != NULL) {
			afisare_student(cursor->info);
			cursor = cursor->next;
		}
	}
}

void afisare_hash(HashGradinita hs) {
	printf("\nAfisare hash: ");
	if (hs.dimensiune == 0 || hs.elemente == NULL) {
		printf("\nNu exista element in hash");
	}
	else {
		for (int i = 0; i < hs.dimensiune; i++) {
			printf("\nElemente pozitia %d: ", i);
			afisare_lista(hs.elemente[i]);
		}
	}
}

int main() {
	FILE* file = fopen("Disciplina.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Disciplina* discipline = (Disciplina*)malloc(sizeof(Disciplina) * nr);

	while (fgets(buffer, 128, file)) {
		Disciplina a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.nrDisciplina = atoi(token);

		token = strtok(NULL, splitter);
		a.nota = atoi(token);

		token = strtok(NULL, splitter);
		a.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.nume, token);

		token = strtok(NULL, splitter);
		a.prenume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.prenume, token);

		discipline[i++] = a;
	}
	printf("\n+++++++++++++++++++++++++Cerinta-1+++++++++++++++++++++++\n");
	HashGradinita hs = alocare_memorie();
	afisare_hash(hs);

	adaugare_studenti_hash(hs, nr, discipline);
	afisare_hash(hs);

	
	printf("\n+++++++++++++++++++++++++Cerinta-3+++++++++++++++++++++++\n");
	Heap heap;

	if (hs.dimensiune < nr) {
		printf("Dimensiunea prea mica");
	}else
	{
	initializare_heap(&heap, hs, nr, 100);
	afisare_heap(heap);
	
	dezalocare_memorie(hs);
	dezalocare_heap(heap);
	}
	
	
}
