#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define DIM_VECTOR 100

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodHeap {
	Student stud;
	int hKey;
};

void filtrareBottomUp(NodHeap* strHeap, int nrNoduri) {
	int offs_curent = nrNoduri - 1;
	int offs_parinte = (offs_curent - 1) / 2;
	while ((offs_parinte != offs_curent) && (strHeap[offs_parinte].hKey < strHeap[offs_curent].hKey)) {
		// conditia de max-heap nu este respectata

		// 1. interschimb continut noduri
		int auxt;
		char* numet;
		char grupat[5];

		// interschimb id-uri
		auxt = strHeap[offs_curent].stud.id;
		strHeap[offs_curent].stud.id = strHeap[offs_parinte].stud.id;
		strHeap[offs_parinte].stud.id = auxt;
		// interschimb nume
		numet = strHeap[offs_curent].stud.nume;
		strHeap[offs_curent].stud.nume = strHeap[offs_parinte].stud.nume;
		strHeap[offs_parinte].stud.nume = numet;
		// interschimb nrGrupa
		strcpy(grupat, strHeap[offs_curent].stud.nrGrupa);
		strcpy(strHeap[offs_curent].stud.nrGrupa, strHeap[offs_parinte].stud.nrGrupa);
		strcpy(strHeap[offs_parinte].stud.nrGrupa, grupat);
		// interschimb chei noduri
		auxt = strHeap[offs_curent].hKey;
		strHeap[offs_curent].hKey = strHeap[offs_parinte].hKey;
		strHeap[offs_parinte].hKey = auxt;
		
		// 2. actualizare offset element curent (cel care urca in arbore)
		offs_curent = offs_parinte;	// noul offset al elementului curent
		offs_parinte = (offs_curent - 1) / 2; // determinare offset pentru noul parinte
	}
}

// !!! Tema filtrare Top/Down nod radacina !!!
void filtrareTopDown(NodHeap* strHeap, int nrNoduri) {
	int offs_curent = nrNoduri - 1;
	int offs_parinte = (offs_curent - 1) / 2;
	while ((offs_parinte != offs_curent) && (strHeap[offs_parinte].hKey > strHeap[offs_curent].hKey)) {
		//nu indeplinesc conditiile de min heap

		//1.interschimbam informatiile celor doua noduri
		int auxt;
		char *numet;
		char grupat[5];

		//interschimb id-uri
		auxt = strHeap[offs_curent].stud.id;
		strHeap[offs_curent].stud.id = strHeap[offs_parinte].stud.id;
		strHeap[offs_parinte].stud.id = auxt;

		//interschimb nume
		numet = strHeap[offs_curent].stud.nume;
		strHeap[offs_curent].stud.nume = strHeap[offs_parinte].stud.nume;
		strHeap[offs_parinte].stud.nume = numet;

		//interschimb nr grupa
		strcpy(grupat, strHeap[offs_curent].stud.nrGrupa);
		strcpy(strHeap[offs_curent].stud.nrGrupa, strHeap[offs_parinte].stud.nrGrupa);
		strcpy(strHeap[offs_parinte].stud.nrGrupa, grupat);

		//interschimb hkey
		auxt = strHeap[offs_curent].hKey;
		strHeap[offs_curent].hKey = strHeap[offs_parinte].hKey;
		strHeap[offs_parinte].hKey = auxt;

		//2. actualizam offseturile
		offs_curent = offs_parinte;
		offs_parinte = (offs_curent - 1) / 2;
	}
}

NodHeap* inserareNodHeap(NodHeap* strHeap, NodHeap nodInserat, int &nrNoduri, int &capacitate) {
	if (nrNoduri == capacitate) {
		// nu mai este spatiu in strHeap pentru a face inserarea unui nou nod
		// realocare strHeap pe o capacitate extinsa cu 100 elemente
		capacitate += DIM_VECTOR;
		NodHeap* strNewHeap = (NodHeap *)malloc(sizeof(NodHeap) * capacitate);

		// copiere elemente din vechea structura heap (la capacitate maxima) in noua structura
		for (int i = 0; i < nrNoduri; i++) {
			strNewHeap[i].stud.id = strHeap[i].stud.id;
			strNewHeap[i].stud.nume = strHeap[i].stud.nume;
			strcpy(strNewHeap[i].stud.nrGrupa, strHeap[i].stud.nrGrupa);
			strNewHeap[i].hKey = strHeap[i].hKey;
		}

		// dezalocare vector la capacitate maxima
		free(strHeap);
			
		// actualizare structura/vector cu noua adresa de vector cu capacitate marita
		strHeap = strNewHeap;
	}

	// strHeap[nrNoduri] = nodInserat;
	strHeap[nrNoduri].stud.id = nodInserat.stud.id;
	strHeap[nrNoduri].stud.nume = nodInserat.stud.nume;
	strcpy(strHeap[nrNoduri].stud.nrGrupa, nodInserat.stud.nrGrupa);
	strHeap[nrNoduri].hKey = nodInserat.hKey;

	nrNoduri += 1;

	filtrareBottomUp(strHeap, nrNoduri);

	return strHeap;
}

// !!! Tema: implementare operatie stergere
//Student stergereNodHeap(NodHeap* strHeap, int &nrNoduri) {
//	Student s;
//	// interschimb primul cu ultimul nod
//
//	// salvare student din ultimul nod in variabila locala pe care o returnam in apelator
//
//	// decrementare nrNoduri
//
//	// filtrare top-down
//
//	// returneaza student din variabila locala
//	return s;
//}

//stergere nod din structura heap
NodHeap* stergereNodHeap(NodHeap* strHeap, int &nrNoduri, int hKey) {
	int i = 0;

	if (hKey == strHeap[nrNoduri - 1].hKey) {
		free(strHeap[nrNoduri - 1].stud.nume);
		nrNoduri = nrNoduri - 1;
		return strHeap;
	}

	while (i < nrNoduri) {
		if (strHeap[i].hKey == hKey) {
			int auxt;
			char* numet;
			char grupat[5];

			//interschimb informatii dintre nodul gasit si ultimul nod
			auxt = strHeap[i].stud.id;
			strHeap[i].stud.id = strHeap[nrNoduri - 1].stud.id;
			strHeap[nrNoduri - 1].stud.id = auxt;

			numet = strHeap[i].stud.nume;
			strHeap[i].stud.nume = strHeap[nrNoduri - 1].stud.nume;
			strHeap[nrNoduri - 1].stud.nume = numet;

			strcpy(grupat, strHeap[i].stud.nrGrupa);
			strcpy(strHeap[i].stud.nrGrupa, strHeap[nrNoduri - 1].stud.nrGrupa);
			strcpy(strHeap[nrNoduri - 1].stud.nrGrupa, grupat);

			auxt = strHeap[i].hKey;
			strHeap[i].hKey = strHeap[nrNoduri - 1].hKey;
			strHeap[nrNoduri - 1].hKey = auxt;

			free(strHeap[nrNoduri - 1].stud.nume);
			nrNoduri = nrNoduri - 1;
			filtrareBottomUp(strHeap, nrNoduri);
			return strHeap;
		}
		i++;
	}
}

void main() {
	NodHeap* vHeap;
	NodHeap nodStud;
	
	int capacitate = DIM_VECTOR;
	vHeap = (NodHeap*)malloc(sizeof(NodHeap) * capacitate);
	// numarul de nouduri existent in structura arbore heap
	int nrNoduri = 0;

	FILE * f;
	f = fopen("StudHeap.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		// alocare (nume) si initializare student
		token = strtok(file_buf, sep_list);
		nodStud.stud.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		nodStud.stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(nodStud.stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(nodStud.stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		nodStud.hKey = atoi(token);

		token = strtok(NULL, sep_list); // verificare existenta token dupa medie in linia curenta file_buf
		if (token)
			printf("\nEroare preluare token!");

		// inserare Student in structura Heap
		inserareNodHeap(vHeap, nodStud, nrNoduri, capacitate);

		nodStud.stud.nume = NULL; // evitare partajare zona heap pentru nume student
	}

	// afisare structura heap
	/*for (int i = 0; i < nrNoduri; i++) {
		printf("%d  ", vHeap[i].hKey);		
	}
	printf("\n");*/

	int i = 0, k = 1, l = nrNoduri / 2 - 2;
	while (i < nrNoduri) {
		int j = 0;
		int ok = 1;
		while (j < k) {
			if (i < nrNoduri) {
				if (ok) {
					ok = 0;
					for (int m = l; m > 0; m--) {
						printf("  ");
					}
				}
				printf("%d  ", vHeap[i].hKey);
				i++;
			}
			j++;
		}
		l--;
		printf("\n");
		k *= 2;
	}

	fclose(f);
}