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
struct NodGradinita {
	Gradinita info;
	NodGradinita* next;
};

struct HashGradinita {
	int dimensiune;
	NodGradinita** elemente;
};
void afisare_student(Gradinita s) {
	printf("\n%d %d %d %s %s", s.cod, s.nrGradinita, s.nrPlozi, s.nume, s.prenume);
}
struct nod {
	Gradinita info;
	nod* next;
	nod* prev;
};


///////////////////Cerinta3 /////////////////////////////

nod* creare_lista(HashGradinita hs, int& nr) {
	if (hs.dimensiune == 0 || hs.elemente == NULL) {
		printf("\nNu exista element in hash");
	}
	else {
		nod* cap = NULL;
		cap = (nod*)malloc(sizeof(nod));
		cap->next = NULL;
		cap->prev = NULL;
		cap->info = hs.elemente[0]->info;
		nod* cursorul, * nou;
		cursorul = cap;
		for (int i = 0; i < hs.dimensiune; i++)
		{	
			if (hs.elemente[i] != NULL) {
				NodGradinita* cursor = hs.elemente[i];
				if (i == 0)
				cursor = cursor->next;
				while (cursor != NULL) 
				{
					nou = (nod*)malloc(sizeof(nod));
					nou->next = NULL;
					nou->prev = cursorul;
					nou->info = cursor->info;
					cursorul->next = nou;
					cursorul = nou;
					cursor = cursor->next;
				}
			}

		}
		return cap;
	}


}
void traversare(nod* cap) {
	printf("\nAfisare lista\n");
	nod* cursor;
	cursor = cap;
	while (cursor) {
		printf("\n%d %d %d %s %s", cursor->info.cod, cursor->info.nrGradinita, cursor->info.nrPlozi, cursor->info.nume, cursor->info.prenume);

		cursor = cursor->next;
	}
}

///////////////////////////////////////////


nod* spargere_lista(nod* cap, int cod) {
	nod* cursor;
	cursor = cap;
	while (cursor !=NULL && cursor->info.cod!=cod) {
		cursor = cursor->next;
	}
	
		nod* capnou;
		capnou = cursor->next;
		capnou->prev = NULL;
		cursor->next = NULL;
	
	return capnou;
}

int cod_hash(char* cheie, HashGradinita hs) {
	return cheie[0] % 255 % hs.dimensiune;

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


int inserare(Gradinita s, HashGradinita& hs) {

	if (hs.dimensiune == 0 || hs.elemente == NULL || s.cod < 0) {
		return -1;
	}
	int hash = cod_hash(s.nume, hs);

	if (hs.elemente[hash] == NULL) {
		hs.elemente[hash] = (NodGradinita*)malloc(sizeof(NodGradinita));
		hs.elemente[hash]->next = NULL;
		hs.elemente[hash]->info = s;
	}
	else {
		NodGradinita* cursor = hs.elemente[hash];
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}

		NodGradinita* nou = (NodGradinita*)malloc(sizeof(NodGradinita));
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
void modificare_cheie(NodGradinita* cap, char* nume) {
	if (cap != NULL) {
		NodGradinita* cursor = cap;
		while (cursor != NULL ) {

			if(!strcmp(cursor->info.nume,nume))
			{
			free(cursor->info.nume);
			cursor->info.nume = (char*)malloc(sizeof(char) * 7);
			strcpy(cursor->info.nume, "numele");

			}
			cursor = cursor->next;
		}
	}
}

void modificare_hash(HashGradinita hs, char* nume) {
	printf("\nParcurgere: ");
	if (hs.dimensiune == 0 || hs.elemente == NULL) {
		printf("\nNu exista element in hash");
	}
	else {
		for (int i = 0; i < hs.dimensiune; i++) {
			modificare_cheie(hs.elemente[i], nume);
		}
	}
}

int main() {
	FILE* file = fopen("Gradinita.txt", "r");
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
	printf("\n+++++++++++++++++++++++++Cerinta 2+++++++++++++++++++++++\n");
	char* nume;
	printf("\nNume: ");
	getchar();
	char buf[30];
	gets_s(buf, 30);
	int dim = strlen(buf) + 1;
	nume = (char*)malloc(sizeof(char) * dim);
	strcpy_s(nume, dim, buf);
	modificare_hash(hs, nume);
	afisare_hash(hs);

	printf("\n++++++++++++++++++++++++Cerinta 3+++++++++++++++++++++++\n");


	nod* cap = NULL;
	printf("\n++++++++++++++++ Citire lista ++++++++++++++\n");
	cap = creare_lista(hs, nr);
	traversare(cap);

	printf("\n++++++++++++++++ Cerinta 4++++++++++++++\n");
	nod* capnou = spargere_lista(cap,5);
	traversare(cap);
	printf("\n++++++++++++++++ Diferenta ++++++++++++++\n");
	traversare(capnou);

	

}