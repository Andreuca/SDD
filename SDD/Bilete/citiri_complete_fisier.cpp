//citire fisier arbore binar de cautare
#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct AparatElectrocasnic {
	int cod;
	int pret;
	char* nume;
	char* cat;
};

struct BinaryTree {
	AparatElectrocasnic info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};
void afisare_apel_urgenta(AparatElectrocasnic apel) {
	printf("\nCod: %d Pret: %d Nume: %s Categorie: %s", apel.cod, apel.pret, apel.nume, apel.cat);
}
void afisare_apeluri_urgenta(AparatElectrocasnic* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_apel_urgenta(apeluri[i]);
	}
}

BinaryTree* creare_nod(AparatElectrocasnic apel, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nod = (BinaryTree*)malloc(sizeof(BinaryTree));
	nod->info = apel;
	nod->dreapta = dreapta;
	nod->stanga = stanga;
	return nod;
}

BinaryTree* inserare_nod(AparatElectrocasnic apel, BinaryTree* radacina) {
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
		afisare_apel_urgenta(radacina->info);
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

int main() {
	FILE* file = fopen("Aparat.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	AparatElectrocasnic* aparate = (AparatElectrocasnic*)malloc(sizeof(AparatElectrocasnic) * nr);

	while (fgets(buffer, 128, file)) {
		AparatElectrocasnic a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.pret = atoi(token);

		;

		token = strtok(NULL, splitter);
		a.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.nume, token);

		token = strtok(NULL, splitter);
		a.cat = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.cat, token);

		aparate[i++] = a;
	}


	BinaryTree* radacina = NULL;
	for (int i = 0; i < nr; i++) {
		radacina = inserare_nod(aparate[i], radacina);
	}
	afisare_preordine(radacina);
}


//Citire lista dubla inlantuita


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct angajat {
	int cod;
	char* nume;
	int salariu;
};

struct nod {
	angajat info;
	nod* next;
	nod* prev;
};

nod* creare_lista(angajat* angajati, int& nr) {
	nod* cap = NULL;
	if (nr > 0) {
		cap = (nod*)malloc(sizeof(nod));
		cap->next = NULL;
		cap->prev = NULL;
		cap->info = angajati[0];
		nod* cursor, * nou;
		cursor = cap;
		for (int i = 1; i < nr; i++) {
			nou = (nod*)malloc(sizeof(nod));
			nou->next = NULL;
			nou->prev = cursor;
			nou->info = angajati[i];
			cursor->next = nou;
			cursor = nou;
		}
	}
	return cap;
}


void traversare(nod* cap) {
	printf("\nAfisare lista\n");
	nod* cursor;
	cursor = cap;
	while (cursor) {
		printf("\nCod: %d; Nume: %s; Salariu: %d", cursor->info.cod, cursor->info.nume, cursor->info.salariu);
		cursor = cursor->next;
	}
}
void dezalocare(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		nod* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}
void main() {
	FILE* file = fopen("Angajati.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	angajat* angajati = (angajat*)malloc(sizeof(angajat) * nr);

	while (fgets(buffer, 128, file)) {
		angajat a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.nume, token);

		token = strtok(NULL, splitter);
		a.salariu = atoi(token);

		angajati[i++] = a;
	}
	nod* cap = NULL;
	printf("\n++++++++++++++++ Citire lista ++++++++++++++\n");
	cap = creare_lista(angajati, nr);
	traversare(cap);

}

//citire din heap aolo....

#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Factura {
	int cod;
	int nrFactura;
	int nrCeva;
	char* numeFactura;
	char* ceva;
};

struct Heap {
	Factura* elemente;
	int dim_maxima;
	int dim_efectiva;
};
void afisare_apel_urgenta(Factura apel) {
	printf("\nCod: %d nrFactura: %d  nrCeva: %d numeFactura: %s ceva: %s", apel.cod, apel.nrFactura, apel.nrCeva, apel.numeFactura, apel.ceva);
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
	if (pozitieFiuStanga < heap.dim_efectiva && heap.elemente[max].nrFactura < heap.elemente[pozitieFiuStanga].nrFactura) {
		max = pozitieFiuStanga;
	}
	if (pozitieFiuDreapta < heap.dim_efectiva &&
		heap.elemente[max].nrFactura < heap.elemente[pozitieFiuDreapta].nrFactura) {
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
			&& heap.elemente[indexFiu].nrFactura > heap.elemente[indexParinte].nrFactura) {
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
int main() {
	FILE* file = fopen("angajati.txt", "r");
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
		a.nrFactura = atoi(token);

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
	printf("\n-------------------------- Alocare Heap ----------------------------------------\n");
	Heap heap;
	initializare_heap(&heap, facturi, nr, 100);
	afisare_heap(heap);

}




//Citire tabela de dispersie --CHAINING
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include<stdio.h>
#include<stdlib.h>

struct Gradinita {
	int cod;
	int nrGradinita;
	int nrPlozi;
	char* nume;
	char* prenume;
};
struct NodStudent {
	Gradinita info;
	NodStudent* next;
};

struct HashGradinita {
	int dimensiune;
	NodStudent** elemente;
};
void afisare_student(Gradinita s) {
	printf("\n%d %d %d %s %s", s.cod, s.nrGradinita, s.nrPlozi, s.nume, s.prenume);
}


int cod_hash(int cheie, HashGradinita hs) {
	return cheie % hs.dimensiune;
}

HashGradinita alocare_memorie() {
	HashGradinita hs;
	printf("\nIntroduceti dimensiunea hash: ");
	scanf_s("%d", &hs.dimensiune);
	hs.elemente = (NodStudent**)malloc(sizeof(NodStudent) * hs.dimensiune);
	for (int i = 0; i < hs.dimensiune; i++) {
		hs.elemente[i] = NULL;
	}
	return hs;
}


int inserare(Gradinita s, HashGradinita& hs) {

	if (hs.dimensiune == 0 || hs.elemente == NULL || s.cod < 0) {
		return -1;
	}
	int hash = cod_hash(s.cod, hs);

	if (hs.elemente[hash] == NULL) {
		hs.elemente[hash] = (NodStudent*)malloc(sizeof(NodStudent));
		hs.elemente[hash]->next = NULL;
		hs.elemente[hash]->info = s;
	}
	else {
		NodStudent* cursor = hs.elemente[hash];
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}

		NodStudent* nou = (NodStudent*)malloc(sizeof(NodStudent));
		nou->info = s;
		nou->next = NULL;

		cursor->next = nou;
	}
	return 1;
}
void adaugare_studenti_hash(HashGradinita& hs, int& nr, Gradinita* gradi) {
	for (int i = 0; i < nr; i++)
	{
		Gradinita s = gradi[i];
		int rezultat = inserare(s, hs);
		printf("\nGradinita cu cod  %d a fost inserat cu %d", s.cod, rezultat);


	}
}
//Dezalocari
void dezalocare_lista(NodStudent* cap) {

	if (cap != NULL) {
		NodStudent* sters;
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


void afisare_lista(NodStudent* cap) {
	if (cap != NULL) {
		NodStudent* cursor = cap;
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
	FILE* file = fopen("angajati.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Gradinita* gradinita = (Gradinita*)malloc(sizeof(Gradinita) * nr);

	while (fgets(buffer, 128, file)) {
		Gradinita a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.nrGradinita = atoi(token);

		token = strtok(NULL, splitter);
		a.nrPlozi = atoi(token);

		token = strtok(NULL, splitter);
		a.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.nume, token);

		token = strtok(NULL, splitter);
		a.prenume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.prenume, token);

		gradinita[i++] = a;
	}
	printf("\n+++++++++++++++++++++++++alocare_memorie+++++++++++++++++++++++\n");
	HashGradinita hs = alocare_memorie();
	afisare_hash(hs);

	adaugare_studenti_hash(hs, nr, gradinita);
	afisare_hash(hs);

}



//Citire tabela dispersie --LINEAR PROBING
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

	Disciplina* gradinita = (Disciplina*)malloc(sizeof(Disciplina) * nr);

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

		gradinita[i++] = a;
	}
	printf("\n+++++++++++++++++++++++++Cerinta-1+++++++++++++++++++++++\n");
	HashGradinita hs = alocare_memorie();
	afisare_hash(hs);

	adaugare_studenti_hash(hs, nr, gradinita);
	afisare_hash(hs);

	//

	dezalocare_memorie(hs);
}



//citire avl
#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Carte {
	int cod;
	int nrCarte;
	int nrPagini;
	char* numeCarte;
	char* autor;
};

struct NodArb {
	Carte info;
	NodArb* stanga;
	NodArb* dreapta;
	int ge;
};
void afisare_carte(Carte c) {
	printf("\ncod: %d nrCarte: %d nrPagini: %d numeCarte: %s autor: %s", c.cod, c.nrCarte, c.nrPagini, c.numeCarte, c.autor);
}
NodArb* creare_nod(Carte c) {
	NodArb* nod = (NodArb*)malloc(sizeof(NodArb));
	nod->dreapta = NULL;
	nod->stanga = NULL;
	nod->ge = 0;
	nod->info = c;
	return nod;
}

void afisare(NodArb* radacina) {
	if (radacina) {
		afisare_carte(radacina->info);
		afisare(radacina->stanga);
		afisare(radacina->dreapta);
	}
}

int inaltime_arbore(NodArb* radacina) {
	if (radacina) {
		int inaltime_stanga = inaltime_arbore(radacina->stanga);
		int inaltime_dreapta = inaltime_arbore(radacina->dreapta);
		return 1 + (inaltime_stanga > inaltime_dreapta ? inaltime_stanga : inaltime_dreapta);
	}
	else {
		return 0;
	}
}

int grad_echilibru(NodArb* radacina) {
	if (radacina) {
		int inaltime_stanga = inaltime_arbore(radacina->stanga);
		int inaltime_dreapta = inaltime_arbore(radacina->dreapta);
		return inaltime_stanga - inaltime_dreapta;
	}
	else {
		return 0;
	}
}

//=================== METODE DE ROTIRE AVL INCEPUT ============================
NodArb* rotire_stanga(NodArb* radacina) {
	if (radacina) {
		NodArb* copil_dreapta = radacina->dreapta;
		radacina->dreapta = copil_dreapta->stanga;
		copil_dreapta->stanga = radacina;
		radacina->ge = grad_echilibru(radacina);
		copil_dreapta->ge = grad_echilibru(copil_dreapta);
		return copil_dreapta;
	}
	else {
		return radacina;
	}
}

NodArb* rotire_dreapta(NodArb* radacina) {
	if (radacina) {
		NodArb* copil_stanga = radacina->stanga;
		radacina->stanga = copil_stanga->dreapta;
		copil_stanga->dreapta = radacina;
		radacina->ge = grad_echilibru(radacina);
		copil_stanga->ge = grad_echilibru(copil_stanga);
		return copil_stanga;
	}
	else {
		return radacina;
	}
}

NodArb* rotire_stanga_dreapta(NodArb* radacina) {
	if (radacina) {
		radacina->stanga = rotire_stanga(radacina->stanga);
		return rotire_dreapta(radacina);
	}
	else {
		return radacina;
	}
}

NodArb* rotire_dreapta_stanga(NodArb* radacina) {
	if (radacina) {
		radacina->dreapta = rotire_dreapta(radacina->dreapta);
		return rotire_stanga(radacina);
	}
	else {
		return radacina;
	}
}
//=================== METODE DE ROTIRE AVL FINAL ============================
NodArb* echilibrare(NodArb* radacina) {
	if (!radacina) {
		return radacina;
	}
	radacina->ge = grad_echilibru(radacina);

	if (radacina->ge == 2) {
		return radacina->stanga->ge == 1
			? rotire_dreapta(radacina)
			: rotire_stanga_dreapta(radacina);
	}

	if (radacina->ge == -2) {
		return radacina->dreapta->ge == -1
			? rotire_stanga(radacina)
			: rotire_dreapta_stanga(radacina);
	}
	return radacina;
}


NodArb* inserare_nod(Carte carte, NodArb* radacina) {
	if (radacina) {
		if (radacina->info.cod > carte.cod) {
			radacina->stanga = inserare_nod(carte, radacina->stanga);
		}
		else {
			radacina->dreapta = inserare_nod(carte, radacina->dreapta);
		}
		return echilibrare(radacina);
	}
	else {
		return creare_nod(carte);
	}
}

void dezalocare(NodArb*& radacina) {
	if (radacina) {
		dezalocare(radacina->dreapta);
		dezalocare(radacina->stanga);
		free(radacina);
		radacina = NULL;
	}
}
int main() {
	FILE* file = fopen("angajati.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Carte* carti = (Carte*)malloc(sizeof(Carte) * nr);

	while (fgets(buffer, 128, file)) {
		Carte a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.nrCarte = atoi(token);

		token = strtok(NULL, splitter);
		a.nrPagini = atoi(token);

		token = strtok(NULL, splitter);
		a.numeCarte = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.numeCarte, token);

		token = strtok(NULL, splitter);
		a.autor = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.autor, token);

		carti[i++] = a;
	}

	NodArb* radacina = NULL;
	for (int i = 0; i < nr; i++) {
		radacina = inserare_nod(carti[i], radacina);
	}
	printf("\nAfisare AVL:\n");
	afisare(radacina);
}


//citire graf

#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Carte {
	int cod;
	int nrCarte;
	int nrPagini;
	char* numeCarte;
	char* autor;
};

struct NodVecin;

struct NodGraf {
	Carte info;
	NodVecin* vecini;
	NodGraf* next;
};

struct NodVecin {
	NodGraf* info;
	NodVecin* next;
};

NodGraf* cautaNodGrafDupaCheie(NodGraf* cap, int cod) {
	NodGraf* cursor = cap;
	while (cursor != NULL && cursor->info.cod != cod) {
		cursor = cursor->next;
	}
	return cursor;
}

NodGraf* adaugareNodGraf(NodGraf* cap, Carte carte) {
	NodGraf* nou = (NodGraf*)malloc(sizeof(NodGraf));
	nou->info = carte;
	nou->next = NULL;
	nou->vecini = NULL;
	if (cap == NULL) {
		return nou;
	}
	NodGraf* cursor = cap;
	while (cursor->next != NULL) {
		cursor = cursor->next;
	}
	cursor->next = nou;
	return cap;
}

NodVecin* adaugareNodVecin(NodVecin* cap, NodGraf* info) {
	NodVecin* nou = (NodVecin*)malloc(sizeof(NodVecin));
	nou->next = NULL;
	nou->info = info;
	if (cap == NULL) {
		return nou;
	}

	NodVecin* cursor = cap;
	while (cursor->next != NULL) {
		cursor = cursor->next;
	}

	cursor->next = nou;

	return cap;
}


void adaugareArcInGraf(NodGraf* cap, int idStart, int idStop) {
	if (cap != NULL) {
		NodGraf* nodStart = cautaNodGrafDupaCheie(cap, idStart);
		NodGraf* nodStop = cautaNodGrafDupaCheie(cap, idStop);
		if (nodStart != NULL && nodStop != NULL) {
			nodStart->vecini = adaugareNodVecin(nodStart->vecini, nodStop);
			nodStop->vecini = adaugareNodVecin(nodStop->vecini, nodStart);
		}
	}
}

void afisareNodVecin(NodVecin* cap) {
	NodVecin* cursor = cap;
	while (cursor != NULL) {
		printf("%d %d %d\n", cursor->info->info.cod, cursor->info->info.nrCarte, cursor->info->info.nrPagini);
		cursor = cursor->next;
	}
}

void afisarNodGraf(NodGraf* cap) {
	NodGraf* cursor = cap;
	while (cursor != NULL) {
		printf("\n%d %d %d are urmatorii vecini:\n", cursor->info.cod, cursor->info.nrCarte, cursor->info.nrPagini);
		afisareNodVecin(cursor->vecini);
		cursor = cursor->next;
	}
}

int numarNoduri(NodGraf* graf) {
	NodGraf* cursor = graf;
	int count = 0;
	while (cursor != NULL) {
		count++;
		cursor = cursor->next;
	}
	return count;
}

int* initializareNoduriVizitate(NodGraf* graf) {
	int nrNoduri = numarNoduri(graf);
	int* noduriVizitate = (int*)malloc(sizeof(int) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		noduriVizitate[i] = 0;
	}
	return noduriVizitate;
}

//================================= METODE LISTA CARTE ================================
struct NodCarte {
	Carte info;
	NodCarte* next;
};

NodCarte* adaugareNodCarte(NodCarte* cap, Carte info) {
	NodCarte* nou = (NodCarte*)malloc(sizeof(NodCarte));
	nou->info = info;
	nou->next = NULL;
	if (cap == NULL) {
		return nou;
	}

	NodCarte* cursor = cap;
	while (cursor->next != NULL) {
		cursor = cursor->next;
	}
	cursor->next = nou;
	return cap;
}

void afisareNodCarte(NodCarte* cap) {
	NodCarte* cursor = cap;
	while (cursor != NULL) {
		printf("%d %d %d\n", cursor->info.cod, cursor->info.nrCarte, cursor->info.nrPagini);
		cursor = cursor->next;
	}
}
struct NodStiva {
	int cod;
	NodStiva* next;
};

void pushStiva(NodStiva*& primul, int cod) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->cod = cod;
	nou->next = NULL;
	if (primul == NULL) {
		primul = nou;
	}
	else {
		nou->next = primul;
		primul = nou;
	}
}

int popStiva(NodStiva*& primul) {
	if (primul) {
		NodStiva* eliminat = primul;
		int cod = primul->cod;
		primul = primul->next;
		free(eliminat);
		return cod;
	}
	return -1;
}

NodCarte* parcurgereAdancime(NodGraf* graf, int idNodStart) {
	if (graf == NULL) {
		return NULL;
	}
	NodCarte* rezultat = NULL;
	int* noduriVizitate = initializareNoduriVizitate(graf);
	NodStiva* stiva = NULL;
	pushStiva(stiva, idNodStart);
	noduriVizitate[idNodStart] = 1;
	while (stiva != NULL) {
		int idNodCurent = popStiva(stiva);
		NodGraf* nodCurent = cautaNodGrafDupaCheie(graf, idNodCurent);
		rezultat = adaugareNodCarte(rezultat, nodCurent->info);
		NodVecin* cursor = nodCurent->vecini;
		while (cursor != NULL) {
			int idVecin = cursor->info->info.cod;
			if (noduriVizitate[idVecin] == 0) {
				pushStiva(stiva, idVecin);
				noduriVizitate[idVecin] = 1;
			}
			cursor = cursor->next;
		}
	}
	return rezultat;
}

Carte citesteCarteFisier(FILE* fisier) {
	Carte c;
	fscanf_s(fisier, "%d", &c.cod);
	fgetc(fisier);

	fscanf_s(fisier, "%d", &c.nrCarte);
	fgetc(fisier);

	fscanf_s(fisier, "%d", &c.nrPagini);
	fgetc(fisier);


	char buf1[30];
	fgets(buf1, 30, fisier);
	int dim1 = strlen(buf1) + 1;
	c.numeCarte = (char*)malloc(sizeof(char) * dim1);
	strcpy_s(c.numeCarte, dim1, buf1);



	char buf2[30];
	fgets(buf2, 30, fisier);
	int dim2 = strlen(buf2) + 1;
	c.autor = (char*)malloc(sizeof(char) * dim2);
	strcpy_s(c.autor, dim2, buf2);

	return c;
}

NodGraf* citesteNodGrafFisier() {
	int n = 0;
	NodGraf* graf = NULL;
	Carte carte;
	FILE* fisier;
	fopen_s(&fisier, "carti.txt", "r");
	if (fisier != NULL) {

		fscanf_s(fisier, "%d", &n);

		for (int i = 0; i < n; i++) {
			carte = citesteCarteFisier(fisier);
			graf = adaugareNodGraf(graf, carte);
		}

		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}

	return graf;
}

void citesteMuchiiGrafFisier(NodGraf*& graf) {
	FILE* fisier;
	fopen_s(&fisier, "graf.txt", "r");
	if (fisier != NULL) {
		int nr_muchii;
		int idStart;
		int idStop;

		fscanf_s(fisier, "%d", &nr_muchii);

		for (int i = 0; i < nr_muchii; i++) {
			fscanf_s(fisier, "%d %d", &idStart, &idStop);
			adaugareArcInGraf(graf, idStart, idStop);
		}

		fclose(fisier);
	}
	else {
		printf("\nFisierul nu se poate deschide");
	}
}

void dezalocareLS(NodVecin* cap) {
	NodVecin* temp = cap;
	while (temp) {
		NodVecin* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(NodGraf* cap) {
	NodGraf* temp = cap;
	while (temp) {
		NodGraf* temp2 = temp->next;
		if (temp->vecini)
			dezalocareLS(temp->vecini);
		printf("\nAm sters %s", temp->info.numeCarte);
		free(temp->info.numeCarte);
		free(temp);
		temp = temp2;
	}
}
void main() {
	printf("\n========================CITIRE NODURI GRAF===============================\n");
	NodGraf* graf = citesteNodGrafFisier();
	afisarNodGraf(graf);
	printf("\n========================ADAUGARE MUCHII===============================\n");
	citesteMuchiiGrafFisier(graf);
	afisarNodGraf(graf);
	printf("\n==========================PARCURGERE DF=============================\n");
	NodCarte* capDf = parcurgereAdancime(graf, 0);
	afisareNodCarte(capDf);
	dezalocareLP(graf);
}