#define _CRT_SECURE_NO_WARNINGS
#define LINESIZE 128
#define ARRAY_SIZE 100

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Disciplina {
	int cod;
	int nrCredite;
	char* denumire;
	char* tipExaminare;
	int semestru;
};

struct NodDisciplina {
	Disciplina info;
	NodDisciplina* next;
};

struct Hash {
	int dimensiune;
	NodDisciplina** elemente;
};

struct Heap {
	Disciplina* elemente;
	int dim_maxima;
	int dim_efectiva;
};

int cod_hash(int cheie, Hash hs) {
	return cheie % hs.dimensiune;
}

Hash alocare_memorie(int dim) {
	Hash hs;
	hs.dimensiune = dim;
	hs.elemente = (NodDisciplina**)malloc(sizeof(NodDisciplina)*hs.dimensiune);
	for (int i = 0; i < hs.dimensiune; i++) {
		hs.elemente[i] = NULL;
	}
	return hs;
}

int inserare(Disciplina d, Hash &hs) {
	if (hs.dimensiune != 0) {
		int nrCluster = 0;
		int hash = cod_hash(d.cod, hs); //cheia de cautare este reprezentata de codul disciplinei
		while (hs.elemente[hash] != NULL) {
			hash = hash + 1;
			nrCluster++;
		}
		if (hash < hs.dimensiune) {
			hs.elemente[hash] = (NodDisciplina*)malloc(sizeof(NodDisciplina));
			hs.elemente[hash]->next = NULL;
			// daca voiam sa partajeze memoria: hs.elemente[hash]->info = d;
			hs.elemente[hash]->info.cod = d.cod;
			hs.elemente[hash]->info.nrCredite = d.nrCredite;
			hs.elemente[hash]->info.denumire = (char*)malloc((strlen(d.denumire) + 1) * sizeof(char));
			strcpy(hs.elemente[hash]->info.denumire, d.denumire);
			hs.elemente[hash]->info.tipExaminare = (char*)malloc((strlen(d.tipExaminare) + 1) * sizeof(char));
			strcpy(hs.elemente[hash]->info.tipExaminare, d.tipExaminare);
			hs.elemente[hash]->info.semestru = d.semestru;
		}
		else
			printf("Elementul cu codul %d nu poate fi inserat", d.cod);

		return nrCluster;
	}
	else
	{
		return 0;
	}
}

void afisare_disciplina(Disciplina d) {
	printf("Cod: %d, Numar Credite: %d, Denumire: %s, Tip Examen: %s, Semestru = %d \n\n", d.cod, d.nrCredite, d.denumire, d.tipExaminare, d.semestru);
}

void afisare_lista(NodDisciplina* cap) {
	if (cap != NULL) {
		NodDisciplina* cursor = cap;
		while (cursor != NULL) {
			afisare_disciplina(cursor->info);
			cursor = cursor->next;
		}
	}
}

void afisare_hash(Hash hs) {
	printf("\nAfisare hash: \n\n");
	if (hs.dimensiune == 0 || hs.elemente == NULL) {
		printf("\nNu exista element in hash");
	}
	else {
		for (int i = 0; i < hs.dimensiune; i++) {
			printf("Elemente pozitia %d: \n", i);
			afisare_lista(hs.elemente[i]);
		}
	}
}

Hash mutare_semestru(Hash hs, int cod) {
	if (hs.dimensiune) {
		for (int i = 0; i < hs.dimensiune; i++) {
			if (hs.elemente[i]->info.cod == cod) {
				if (hs.elemente[i]->info.semestru == 1) {
					hs.elemente[i]->info.semestru = 2;
				}
				else {
					hs.elemente[i]->info.semestru = 1;
				}
			}
		}
	}
	return hs;
}

void interschimbare(Heap &heap, int min, int pozitie) {
	Disciplina aux = heap.elemente[min];
	heap.elemente[min] = heap.elemente[pozitie];
	heap.elemente[pozitie] = aux;
}

void filtrare(Heap &heap, int parinte) {
	int pozitieFiuStanga = 2 * parinte + 1;
	int pozitieFiuDreapta = 2 * parinte + 2;
	int min = parinte;
	if (pozitieFiuStanga < heap.dim_efectiva &&
		heap.elemente[min].nrCredite < heap.elemente[pozitieFiuStanga].nrCredite) {
		min = pozitieFiuStanga;
	}
	if (pozitieFiuDreapta < heap.dim_efectiva &&
		heap.elemente[min].nrCredite < heap.elemente[pozitieFiuDreapta].nrCredite) {
		min = pozitieFiuDreapta;
	}
	if (min != parinte) {
		interschimbare(heap, min, parinte);
		filtrare(heap, min);
	}
}

void initializare_heap(Heap *heap, Hash hs, int dimensiune_maxima)
{
	heap->dim_maxima = dimensiune_maxima;
	heap->dim_efectiva = 0;
	heap->elemente = (Disciplina*)malloc(sizeof(Disciplina)*hs.dimensiune);
	for (int i = 0; i < hs.dimensiune; i++)
	{
		if (hs.elemente[i]->info.semestru == 2) {
			heap->elemente[heap->dim_efectiva].cod = hs.elemente[i]->info.cod;
			heap->elemente[heap->dim_efectiva].nrCredite = hs.elemente[i]->info.nrCredite;
			heap->elemente[heap->dim_efectiva].denumire = (char*)malloc((strlen(hs.elemente[i]->info.denumire) + 1) * sizeof(char));
			strcpy(heap->elemente[heap->dim_efectiva].denumire, hs.elemente[i]->info.denumire);
			heap->elemente[heap->dim_efectiva].tipExaminare = (char*)malloc((strlen(hs.elemente[i]->info.tipExaminare) + 1) * sizeof(char));
			strcpy(heap->elemente[heap->dim_efectiva].tipExaminare, hs.elemente[i]->info.tipExaminare);
			heap->elemente[heap->dim_efectiva].semestru = hs.elemente[i]->info.semestru;

			heap->dim_efectiva++;
		}
	}
	for (int i = (heap->dim_efectiva - 1) / 2; i >= 0; i--)
	{
		filtrare(*heap, i);
	}
}

void inserare_heap(Heap &heap, Disciplina d) {
	if (heap.dim_efectiva < heap.dim_maxima) {
		Disciplina* temp = (Disciplina*)malloc(sizeof(Disciplina)*(heap.dim_efectiva + 1));
		for (int i = 0; i < heap.dim_efectiva; i++) {
			temp[i] = heap.elemente[i];
		}
		temp[heap.dim_efectiva] = d;
		free(heap.elemente);
		heap.dim_efectiva++;
		heap.elemente = temp;

		int indexFiu = heap.dim_efectiva - 1;
		int indexParinte = (indexFiu - 1) / 2;

		while (indexParinte >= 0
			&& heap.elemente[indexFiu].nrCredite < heap.elemente[indexParinte].nrCredite) {
			interschimbare(heap, indexFiu, indexParinte);
			indexFiu = indexParinte;
			indexParinte = (indexFiu - 1) / 2;
		}
	}
	else {
		printf("\nNu mai este loc disponibil in heap");
	}
}

void afisare_heap(Heap heap) {
	for (int i = 0; i < heap.dim_efectiva; i++) {
		afisare_disciplina(heap.elemente[i]);
	}
}

void puncteColiziune(Hash hs) {
	printf("\nPuncte de coliziune: ");
	int ok = 0;
	for (int i = 0; i < hs.dimensiune; i++) {
		int cod = cod_hash(hs.elemente[i]->info.cod, hs);
		if(cod != i) {
			ok++;
		}
	}
	printf("%d", ok);
}

void dezalocare_lista(NodDisciplina* cap) {
	if (cap != NULL) {
		NodDisciplina* sters;
		while (cap != NULL) {
			sters = cap;
			cap = cap->next;
			free(sters);
		}
	}
}
void dezalocare_memorie(Hash hs) {
	if (hs.dimensiune > 0 && hs.elemente != NULL) {
		for (int i = 0; i < hs.dimensiune; i++) {
			dezalocare_lista(hs.elemente[i]);
		}
		free(hs.elemente);
		hs.dimensiune = 0;
	}
}

void dezalocare_heap(Heap heap) {
	if (heap.dim_efectiva > 0 && heap.elemente != NULL) {
		free(heap.elemente);
	}
}

int main() {
	FILE* file = fopen("discipline.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Disciplina* vector = (Disciplina*)malloc(sizeof(Disciplina) * nr);

	while (fgets(buffer, 128, file)) {
		Disciplina a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.nrCredite = atoi(token);

		token = strtok(NULL, splitter);
		a.denumire = (char*)malloc(sizeof(char)*(strlen(token) + 1));
		strcpy(a.denumire, token);

		token = strtok(NULL, splitter);
		a.tipExaminare = (char*)malloc(sizeof(char)*(strlen(token) + 1));
		strcpy(a.tipExaminare, token);

		token = strtok(NULL, splitter);
		a.semestru = atoi(token);

		vector[i++] = a;
	}

	Hash hash = alocare_memorie(i);
	int cluster = 0;
	for (int i = 0; i < hash.dimensiune; i++) {
		int aux = inserare(vector[i], hash); // daca voiam o inserare basic, faceam functia void si stergeam return si aux, dar am vrut sa verific rezultatul de la exercitiul 4
		cluster = cluster + aux;
	}
	printf("\n--------------- Afisare HashTable --------------\n\n");
	afisare_hash(hash); 

	printf("\n--------------- Afisare HashTable dupa modificarea semestrului --------------\n\n");
	hash = mutare_semestru(hash, 3); //modifica semestrul materiei al carei cod este precizat in antent
	afisare_hash(hash);

	Heap heap;
	initializare_heap(&heap, hash, 100); // heap-ul contine toate materiile din semestrul 2, prioritizarea se face in functie de numarul de credite, am ales sa implementez un Max-Heap, daca voiam Min-Heap schimbam 2 semne din < in > in functia de filtrare
	printf("\n--------- Afisare Heap cu materiile din semestrul al doilea ---------\n\n");
	afisare_heap(heap);

	puncteColiziune(hash);

	printf("\nNumar Clustere (rezultat identificat in functia inserare in HashTable): %d  **just in case**\n\n", cluster); // doar pentru a verifica daca este okay
	
	free(vector);
	dezalocare_memorie(hash);
	dezalocare_heap(heap);
}