#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct angajat {
	int cod;
	char* nume;
	float salariu;
};

struct nod {
	angajat info;
	nod* next;
};

angajat citire_angajat_tastatura() {
	angajat a;
	printf("\nCitire angajat:\n");
	printf("\nCod: ");
	scanf_s("%d", &a.cod);
	printf("\nNume: ");
	getchar();
	char buf[30];
	gets_s(buf, 30);
	int dim = strlen(buf) + 1;
	a.nume = (char*)malloc(sizeof(char) * dim);
	strcpy_s(a.nume, dim, buf);
	printf("\nSalariu: ");
	scanf_s("%f", &a.salariu);
	return a;
}
nod* creare_lista_circulara() {
	nod* cap = NULL;
	int nr_el = 0;
	printf("\nIntroduceti numarul de elemente: ");
	scanf_s("%d", &nr_el);
	if (nr_el > 0) {
		cap = (nod*)malloc(sizeof(nod));
		cap->next = NULL;
		cap->info = citire_angajat_tastatura();
		nod* cursor, * nou;
		cursor = cap;
		for (int i = 1; i < nr_el; i++) {
			nou = (nod*)malloc(sizeof(nod));
			nou->next = NULL;
			nou->info = citire_angajat_tastatura();
			cursor->next = nou;
			cursor = nou;
		}
		cursor->next = cap;
	}
	return cap;
}

nod* inserare_element_circulara(nod* cap, angajat info) {
	if (cap == NULL) {
		cap = (nod*)malloc(sizeof(nod));
		cap->info = info;
		cap->next = cap;
	}
	else
	{
		nod* cursor = cap;
		while (cursor->next != cap) {
			cursor = cursor->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->next = cap;
		nou->info = info;
		cursor->next = nou;
	}
	return cap;
}

nod* stergere_element_circulara(nod* cap) {
	if (cap == NULL) {
		return NULL;
	}
	else if (cap->next == cap) {
		free(cap);
		return NULL;
	}
	else {
		nod* cursor = cap;
		while (cursor->next->next != cap) {
			cursor = cursor->next;
		}
		nod* ultim = cursor->next;
		cursor->next = cap;
		free(ultim);
		return cap;
	}
}

void traversare_circulara(nod* cap) {
	printf("\nAfisare lista\n");
	nod* cursor;
	cursor = cap;
	do {
		printf("\nCod: %d; Nume: %s; Salariu: %5.2f", cursor->info.cod, cursor->info.nume, cursor->info.salariu);
		cursor = cursor->next;
	} while (cursor != cap);
}

nod* creare_lista() {
	nod* cap = NULL;
	int nr_el = 0;
	printf("\nIntroduceti numarul de elemente: ");
	scanf_s("%d", &nr_el);
	if (nr_el > 0) {
		cap = (nod*)malloc(sizeof(nod));
		cap->next = NULL;
		cap->info = citire_angajat_tastatura();
		nod* cursor, * nou; 
		cursor = cap;
		for (int i = 1; i < nr_el; i++) {
			nou = (nod*)malloc(sizeof(nod));
			nou->next = NULL;
			nou->info = citire_angajat_tastatura();
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
		printf("\nCod: %d; Nume: %s; Salariu: %5.2f", cursor->info.cod, cursor->info.nume, cursor->info.salariu);
		cursor = cursor->next;
	}
}

nod* inserare_element(nod* cap, angajat info) {
	if (cap == NULL) {
		cap = (nod*)malloc(sizeof(nod));
		cap->info = info;
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
		nou->info = info;
		cursor->next = nou;
	}
	return cap;
}

nod* stergere_element(nod* cap) {
	if (cap == NULL) {
		return NULL;
	}
	else if (cap->next == NULL) {
		free(cap);
		return NULL;
	}
	else {
		nod* cursor = cap;
		while (cursor->next->next != NULL) {
			cursor = cursor->next;
		}
		nod* ultim = cursor->next;
		cursor->next = NULL;
		free(ultim);
		return cap;
	}
}

int nr_noduri(nod* cap) {
	int nr = 0;
	nod* cursor = cap;
	while (cursor) {
		cursor = cursor->next;
		nr++;
	}
	return nr;
}

int inserare_element_pozitie(nod*& cap, angajat a, int poz) {
	int rezultat = 0;
	int nr = nr_noduri(cap);
	printf("\nLista are %d elemente", nr);
	if ((poz < 0) || (poz > nr)) {
		rezultat = -1;
	}
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = a;
	if (poz == 0) {
		nou->next = cap;
		cap = nou;
		rezultat = 1;
	}
	else {
		int contor = 0;
		nod* cursor = cap;
		while (cursor->next != NULL && contor < poz - 1) {
			cursor = cursor->next;
			contor++;
		}
		nou->next = cursor->next;
		cursor->next = nou;
		rezultat = 1;
	}
	return rezultat;
}

int stergere_pozitie(nod*& cap, int pozitie)
{
	int rezultat = 0;
	int nr = nr_noduri(cap);
	if ((pozitie >= nr) || (pozitie < 0)) {
		rezultat = -1;
	}
	nod* cursor;
	if (pozitie == 0)
	{
		cursor = cap;
		cap = cap->next;
		free(cursor);
		rezultat = -1;
	}
	else
	{
		int contor = 0;
		cursor = cap;
		while (contor < pozitie - 1)
		{
			cursor = cursor->next;
			contor++;
		}
		nod* eliminat = cursor->next;
		cursor->next = eliminat->next;
		free(eliminat);
		rezultat = 1;
	}
	return rezultat;
}

void main() {
	nod* cap = NULL;
	cap = creare_lista();
	traversare(cap);
	cap = stergere_element(cap);
	traversare(cap);
	angajat a = citire_angajat_tastatura();
	cap = inserare_element(cap, a);
	traversare(cap);
	int pozitie;
	printf("\nIntroduceti pozitia: ");
	scanf_s("%d", &pozitie);
	int rez = inserare_element_pozitie(cap, a, pozitie);
	traversare(cap);
	printf("\nIntroduceti pozitia: ");
	scanf_s("%d", &pozitie);
	rez = stergere_pozitie(cap, pozitie);
	traversare(cap);
}