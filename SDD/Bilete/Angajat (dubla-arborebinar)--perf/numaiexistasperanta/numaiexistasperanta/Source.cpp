#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct angajat {
	int cod;
	int salariu;
	int nrAngajat;
	char* nume;
	char* prenume;
};

struct nod {
	angajat info;
	nod* next;
	nod* prev;
};

struct BinaryTree {
	angajat info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};


//////////////////////////////////////////////////////////////
void afisare_apel_urgenta(angajat apel) {
	printf("\nCod: %d; Salariu: %d; nrAngajat: %d; Nume: %s; Prenume: %s", apel.cod, apel.salariu, apel.nrAngajat, apel.nume, apel.prenume);
}
void afisare_apeluri_urgenta(angajat* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_apel_urgenta(apeluri[i]);
	}
}

BinaryTree* creare_nod(angajat apel, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nod = (BinaryTree*)malloc(sizeof(BinaryTree));
	nod->info.cod = apel.cod;
	nod->info.salariu = apel.salariu;
	nod->info.nrAngajat = apel.nrAngajat;
	//
	nod->info.nume = (char*)malloc(sizeof(char) * (strlen(apel.nume)));
	nod->info.prenume = (char*)malloc(sizeof(char) * (strlen(apel.prenume)));
	strcpy(nod->info.nume, apel.nume);
	strcpy(nod->info.prenume, apel.prenume);
	//

	nod->dreapta = dreapta;
	nod->stanga = stanga;
	return nod;
}

BinaryTree* inserare_nod(angajat apel, BinaryTree* radacina) {
	if (radacina) {
		if (radacina->info.salariu > apel.salariu) {
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
void copiere_arbore(nod* cap, int nrAngajat,BinaryTree* &radacina) {
	nod* cursor;
	cursor = cap;


	while (cursor ) {
		if (cursor->info.nrAngajat == nrAngajat) {
			radacina = inserare_nod(cursor->info, radacina);
			}
			cursor = cursor->next;
	}
}

void afisare_preordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_apel_urgenta(radacina->info);
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
	}
}

///////////////////////////////////////////////////


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
		printf("\nCod: %d; Salariu: %d; nrAngajat: %d; Nume: %s; Prenume: %s; ", cursor->info.cod, cursor->info.salariu, cursor->info.nrAngajat, cursor->info.nume, cursor->info.prenume);
		cursor = cursor->next;
	}
}


void stergere_pozitie(nod*& cap, int cod){
		nod* cursor;
		cursor = cap;
		if (cursor->info.cod==cod)
		{
			cap = cap->next;
			cap->prev = NULL;
			free(cursor);
		}
		else {
			while (cursor->info.cod != cod && cursor->next != NULL)
			{
				cursor = cursor->next;

			}		
				nod* anterior = cursor->prev;
				nod* urmator = cursor->next;
				cursor->next = NULL;
				cursor->prev = NULL;
				anterior->next = urmator;
				if (urmator!=NULL)
				{
				urmator->prev = anterior;
				}
				free(cursor);
		}	
	}
	


void alocare_vector(BinaryTree* radacina, angajat* va, int &i) {
	if (radacina) {
		if (radacina->info.salariu != 230) {
		va[i] = radacina->info;
		i++;
		alocare_vector(radacina->stanga,va,i);
		alocare_vector(radacina->dreapta,va,i);
		}
		
	}
}

//Dezalocari
void dezalocare_lista(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		nod* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocare(BinaryTree*& radacina) {
	if (radacina) {
		dezalocare(radacina->dreapta);
		dezalocare(radacina->stanga);
		free(radacina);
		radacina = NULL;
	}
}
void dezalocare_vector(angajat* va ) {
	free(va);
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
		a.salariu = atoi(token);

		token = strtok(NULL, splitter);
		a.nrAngajat = atoi(token);

		token = strtok(NULL, splitter);
		a.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.nume, token);

		token = strtok(NULL, splitter);
		a.prenume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.prenume, token);

		angajati[i++] = a;
	}
	nod* cap = NULL;
	printf("\n\n++++++++++++++++ Cerinta-1 ++++++++++++++\n");
	cap = creare_lista(angajati, nr);
	traversare(cap);
	printf("\n++++++++++++++++ Cerinta-2 ++++++++++++++\n");
	stergere_pozitie(cap, 3);
	traversare(cap);
	printf("\n\n++++++++++++++++ Cerinta-3 ++++++++++++++\n");
	BinaryTree* radacina = NULL;
	copiere_arbore(cap, 11, radacina);
	afisare_preordine(radacina);
	printf("\n\n++++++++++++++++ Cerinta-4 ++++++++++++++\n\n");
	angajat* va= (angajat*)malloc(sizeof(angajat)*nr);
	int k = 0;
	alocare_vector(radacina,va,k);
	for (int j = 0; j < k; j++) {
		afisare_apel_urgenta(va[j]);
	}


	dezalocare(radacina);
	dezalocare_lista(cap);
	dezalocare_vector(va);
}