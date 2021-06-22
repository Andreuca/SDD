#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Angajat {
	char nume[30];
	float salariu;
};

struct nod_stiva {
	Angajat info;
	nod_stiva* next_stack;
};

struct nod_coada {
	Angajat info;
	nod_coada* next_queue;
};

Angajat citire_angajat_tastatura() {
	Angajat a;
	printf("\n+++++++++++++++++++++++++++++++++++++++\n");
	printf("Introducere angajat:");
	printf("\nNume: ");
	gets_s(a.nume, 30);
	printf("\nSalariu: ");
	scanf_s("%f", &a.salariu);
	return a;
}

void afisare_angajat_tastatura(Angajat a) {
	printf("\n Nume: %s, Salariu: %2.2f", a.nume, a.salariu);
}

//------------------- STIVA ------------------------------------
void push(nod_stiva*& primul, Angajat info) {
	nod_stiva* nou = (nod_stiva*)malloc(sizeof(nod_stiva));
	nou->info = info;
	nou->next_stack = NULL;
	if (primul == NULL) {
		primul = nou;
	}
	else {
		nou->next_stack = primul;
		primul = nou; 
	}
}
void pop(nod_stiva*& primul, Angajat& info) {
	if (primul) {
		nod_stiva* eliminat = primul;
		info = primul->info;
		primul = primul->next_stack;
		free(eliminat);
	}
}

void afisare_stiva(nod_stiva* primul) {
	nod_stiva* cursor = primul;
	while (cursor) {
		afisare_angajat_tastatura(cursor->info);
		cursor = cursor->next_stack;
	}
}

nod_stiva* intializare_stiva() {
	nod_stiva* primul = NULL;
	int ok = 1;
	while (ok == 1) {
		Angajat a = citire_angajat_tastatura();
		push(primul, a);
		printf("\nDoriti sa continuati? Da-1/Nu-0 ");
		scanf_s("%d", &ok);
		getc(stdin);
	}
	return primul;
}


//------------------- COADA ------------------------------------

void push(nod_coada*& primul, nod_coada*& ultimul, Angajat info) {
	nod_coada* nou = (nod_coada*)malloc(sizeof(nod_coada));
	nou->info = info;
	nou->next_queue = NULL;
	if (primul == NULL && ultimul == NULL) {
		primul = nou;
		ultimul = nou;
	}
	else {
		ultimul->next_queue = nou;
		ultimul = nou;
	}
}
void pop(nod_coada*& primul, nod_coada*& ultimul, Angajat& info) {
	if (primul) {
		nod_coada* eliminat = primul;
		info = primul->info;
		primul = primul->next_queue;
		if (primul == NULL) {
			ultimul = NULL;
		}
		free(eliminat);
	}
}
void afisare_coada(nod_coada* primul) {
	nod_coada* cursor = primul;
	while (cursor) {
		afisare_angajat_tastatura(cursor->info);
		cursor = cursor->next_queue;
	}
}



void initializare_coada(nod_coada** primul, nod_coada** ultimul) {
	int ok = 1;
	while (ok == 1) {
		Angajat a = citire_angajat_tastatura();
		push(*primul, *ultimul, a);
		printf("\nDoriti sa continuati? Da-1/Nu-0 ");
		scanf_s("%d", &ok);
		getc(stdin);
	}
}
void main() {
	printf("\n +++++++++++++++++ STIVA +++++++++++++++++++++++++");
	nod_stiva* primul = intializare_stiva();
	afisare_stiva(primul);
	Angajat a;
	printf("\nScoatere element stiva\n");
	pop(primul, a);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	afisare_stiva(primul);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n Afisare angajat scos din stiva: ");
	afisare_angajat_tastatura(a);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n +++++++++++++++++ COADA +++++++++++++++++++++++++");
	nod_coada* primul_c = NULL;
	nod_coada* ultimul_c = NULL;
	initializare_coada(&primul_c, &ultimul_c);
	afisare_coada(primul_c);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	pop(primul_c, ultimul_c, a);
	afisare_coada(primul_c);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n Afisare angajat scos din coada: ");
	afisare_angajat_tastatura(a);
}