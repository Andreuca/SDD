#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define DIM 100
#define LINESIZE 128

struct Disciplina {
	int id;
	int nrOre;
	char* numeDisciplina;
	char* profesor;
	char* semestru;
};

struct Nod {
	Disciplina d;
	Nod* next;
};

struct NodHeap {
	Disciplina d;
};

int functieHash(char* str, int size) {
	int temp = 0, poz;
	for (int i = 0; i < strlen(str); i++)
		temp += str[i];
	poz = temp % size;

	return poz;
}

void inserareHTable(Nod** hTable, Disciplina d, int size) {
	int k = functieHash(d.numeDisciplina, size);
	char ok = 0;
	int l = k;
	while (k < 100 && ok != 1) {
		if (hTable[k] == NULL) {
			hTable[k] = (Nod*)malloc(sizeof(Nod));
			hTable[k]->d.id = d.id;
			hTable[k]->d.nrOre = d.nrOre;
			hTable[k]->d.numeDisciplina = d.numeDisciplina;
			hTable[k]->d.semestru = d.semestru;
			hTable[k]->d.profesor = d.profesor;
			hTable[k]->next = NULL;
			ok = 1;
		}
		k++;
	}
	if (ok == 0) {
		//hTable[l] = inserareSfarsitLista(hTable[l], d);
		printf("\nNu s-a putut efectua introducerea!");
	}
		
}

void parsareHTable(Nod** hTab, int size) {
	printf("\nAfisare Hash Table:");
	for (int i = 0; i < size; i++) {
		if (hTab[i]) {
			Nod* temp = hTab[i];
			printf("\nAfisare lista %d:\n", i);
			while (temp) {
				printf("ID: %d   Numar ore: %d   Nume Disciplina: %s   Nume Profesor: %s   Semestru: %s", temp->d.id, temp->d.nrOre, temp->d.numeDisciplina, temp->d.profesor, temp->d.semestru);
				temp = temp->next;
			}
		}
	}
}

void mutareSemestru(Nod** hTab, int size) {
	for (int i = 0; i < size; i++) {
		if (hTab[i]) {
			Nod* temp = hTab[i];
			while (temp) {
				if (strcmp(temp->d.semestru, "SemI\n") == 0) {
					free(temp->d.semestru);
					temp->d.semestru = (char*)malloc(sizeof(char) * (strlen("SemII") + 1));
					strcpy(temp->d.semestru, "SemII");
				}
				else {
					free(temp->d.semestru);
					temp->d.semestru = (char*)malloc(sizeof(char) * (strlen("SemI") + 1));
					strcpy(temp->d.semestru, "SemI");
				}
				temp = temp->next;
			}
		}
	}
}

void filtrareBottomUp(NodHeap* strHeap, int nrNoduri) {
	int offs_curent = nrNoduri - 1;
	int offs_parinte = (offs_curent - 1) / 2;

	while ((offs_curent != offs_parinte) && (strHeap[offs_parinte].d.nrOre < strHeap[offs_curent].d.nrOre)) {
		int auxt;
		char *numet;

		auxt = strHeap[offs_curent].d.id;
		strHeap[offs_curent].d.id = strHeap[offs_parinte].d.id;
		strHeap[offs_parinte].d.id = auxt;

		auxt = strHeap[offs_curent].d.nrOre;
		strHeap[offs_curent].d.nrOre = strHeap[offs_parinte].d.nrOre;
		strHeap[offs_parinte].d.nrOre = auxt;

		numet = strHeap[offs_curent].d.numeDisciplina;
		strHeap[offs_curent].d.numeDisciplina = strHeap[offs_parinte].d.numeDisciplina;
		strHeap[offs_parinte].d.numeDisciplina = numet;

		numet = strHeap[offs_curent].d.profesor;
		strHeap[offs_curent].d.profesor = strHeap[offs_parinte].d.profesor;
		strHeap[offs_parinte].d.profesor = numet;

		numet = strHeap[offs_curent].d.semestru;
		strHeap[offs_curent].d.semestru = strHeap[offs_parinte].d.semestru;
		strHeap[offs_parinte].d.semestru = numet;

		offs_curent = offs_parinte;
		offs_parinte = (offs_curent - 1) / 2;
	}
}

NodHeap* inserareHeap(NodHeap* strHeap, Nod** hTab, int &nrNoduri, int &capacitate, int size) {
	for (int i = 0; i < size; i++) {
		if (hTab[i]) {
			Nod* nodInserat = hTab[i];
			if (nodInserat->d.nrOre > 70) {
				if (nrNoduri == capacitate) {
					capacitate += DIM;
					NodHeap* strNewHeap = (NodHeap*)malloc(sizeof(NodHeap) * capacitate);

					for (int i = 0; i < nrNoduri; i++) {
						strNewHeap[i].d.id = strHeap[i].d.id;
						strNewHeap[i].d.nrOre = strHeap[i].d.nrOre;
						strNewHeap[i].d.numeDisciplina = strHeap[i].d.numeDisciplina;
						strNewHeap[i].d.profesor = strHeap[i].d.profesor;
						strNewHeap[i].d.semestru = strHeap[i].d.semestru;
					}

					free(strHeap);
					strHeap = strNewHeap;
				}

				strHeap[nrNoduri].d.id = nodInserat->d.id;
				strHeap[nrNoduri].d.nrOre = nodInserat->d.nrOre;
				strHeap[nrNoduri].d.numeDisciplina = (char*)malloc(sizeof(char) * (strlen(nodInserat->d.numeDisciplina) + 1));
				strcpy(strHeap[nrNoduri].d.numeDisciplina, nodInserat->d.numeDisciplina);
				strHeap[nrNoduri].d.profesor = (char*)malloc(sizeof(char) * (strlen(nodInserat->d.profesor) + 1));
				strcpy(strHeap[nrNoduri].d.profesor, nodInserat->d.profesor);
				strHeap[nrNoduri].d.semestru = (char*)malloc(sizeof(char) * (strlen(nodInserat->d.semestru) + 1));
				strcpy(strHeap[nrNoduri].d.semestru, nodInserat->d.semestru);
					
				nrNoduri++;
				filtrareBottomUp(strHeap, nrNoduri);
			}
		}
	}
	return strHeap;
}

void determinareClustere(Nod** hTab, int size, int* nrClustere) {
	int l = 0;
	for (int i = 0; i < size; i++) {
		if (hTab[i]) {
			l++;
		}
		else if (l > 0) {
			l = 0;
			(*nrClustere)++;
		}
	}
}

void dezalocareTabelaDispersie(Nod** hTab, int size) {
	for (int i = 0; i < size; i++) {
		if (hTab[i]) {
			Nod* temp = hTab[i];
			while (temp) {
				Nod* temp2 = temp;
				temp = temp->next;
				free(temp2->d.numeDisciplina);
				free(temp2->d.profesor);
				free(temp2->d.semestru);
				free(temp2);
			}
		}
	}
	free(hTab);
}

void dezalocareHeap(NodHeap* h, int nrNoduri) {
	for (int i = 0; i < nrNoduri; i++) {
		free(h[i].d.numeDisciplina);
		free(h[i].d.profesor);
		free(h[i].d.semestru);
	}
	free(h);
}

void main() {
	Nod** hTab;
	hTab = (Nod**)malloc(sizeof(Nod*) * DIM);
	for (int i = 0; i < DIM; i++)
		hTab[i] = NULL;
	Disciplina d;

	FILE* f = fopen("Disciplina.txt", "r");
	char *token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		d.id = atoi(token);

		token = strtok(NULL, sep_list);
		d.nrOre = atoi(token);

		token = strtok(NULL, sep_list);
		d.numeDisciplina = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(d.numeDisciplina, token);

		token = strtok(NULL, sep_list);
		d.profesor = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(d.profesor, token);

		token = strtok(NULL, sep_list);
		d.semestru = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(d.semestru, token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("Eroare preluare token din fisier!");

		inserareHTable(hTab, d, DIM);

		d.numeDisciplina = NULL;
		d.profesor = NULL;
		d.semestru = NULL;
	}
	fclose(f);

	parsareHTable(hTab, DIM);

	mutareSemestru(hTab, DIM);
	parsareHTable(hTab, DIM);

	int capacitate = DIM;
	NodHeap* vHeap = (NodHeap*)malloc(sizeof(NodHeap) * capacitate);
	int nrNoduri = 0;
	printf("\nAfisare numar ore dupa introducere noduri in structura Heap:\n");
	vHeap = inserareHeap(vHeap, hTab, nrNoduri, capacitate, DIM);
	for (int i = 0; i < nrNoduri; i++)
		printf(" %d ", vHeap[i].d.nrOre);

	int nrClustere = 0;
	determinareClustere(hTab, DIM, &nrClustere);
	printf("\nNumarul de clustere este: %d.", nrClustere);

	dezalocareTabelaDispersie(hTab, DIM);
	dezalocareHeap(vHeap, nrNoduri);
}