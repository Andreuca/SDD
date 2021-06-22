
#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Carte {
	int id;
	char titlu[50];
	float pret;
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

NodGraf* cautaNodGrafDupaCheie(NodGraf* cap, int id) {
	NodGraf* cursor = cap;
	while (cursor != NULL && cursor->info.id != id) {
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
	while (cursor->next!=NULL) {
		cursor = cursor->next;
	}

	cursor->next = nou;

	return cap;
}


void adaugareArcInGraf(NodGraf* cap, int idStart, int idStop) {
	if (cap!=NULL){
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
		printf("  %d %s %f\n", cursor->info->info.id,cursor->info->info.titlu, cursor->info->info.pret);
		cursor = cursor->next;
	}
}

void afisarNodGraf(NodGraf* cap) {
	NodGraf* cursor = cap;
	while (cursor != NULL) {
		printf("\n%d %s %f are urmatorii vecini:\n", cursor->info.id,cursor->info.titlu, cursor->info.pret);
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
	int* noduriVizitate = (int*)malloc(sizeof(int)*nrNoduri);
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
		printf("%d %s %f\n", cursor->info.id, cursor->info.titlu, cursor->info.pret);
		cursor = cursor->next;
	}
}

//============================== PARCURGERE DF =================================

struct NodStiva {
	int id;
	NodStiva* next;
};

void pushStiva(NodStiva* &primul, int id) {
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->id = id;
	nou->next = NULL;
	if (primul == NULL) {
		primul = nou;
	}
	else {
		nou->next = primul;
		primul = nou;
	}
}

int popStiva(NodStiva* &primul) {
	if (primul) {
		NodStiva* eliminat = primul;
		int id = primul->id;
		primul = primul->next;
		free(eliminat);
		return id;
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
			int idVecin = cursor->info->info.id;
			if (noduriVizitate[idVecin] == 0) {
				pushStiva(stiva, idVecin);
				noduriVizitate[idVecin] = 1;
			}
			cursor = cursor->next;
		}
	}
	return rezultat;
}

//============================== PARCURGERE BF =================================

struct NodCoada {
	int id;
	NodCoada* next;
};

void pushCoada(NodCoada* &primul, NodCoada* &ultimul, int id) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = NULL;
	if (primul == NULL && ultimul == NULL) {
		primul = nou;
		ultimul = nou;
	}
	else {
		ultimul->next = nou;
		ultimul = nou;
	}
}
int popCoada(NodCoada* &primul, NodCoada* &ultimul) {
	if (primul!=NULL) {
		NodCoada* eliminat = primul;
		int id = primul->id;
		primul = primul->next;
		if (primul == NULL) {
			ultimul = NULL;
		}
		
		free(eliminat);
		return id;
	}
	return -1;
}

NodCarte* parcurgereLatime(NodGraf* graf, int idNodStart) {
	if (graf == NULL) {
		return NULL;
	}
	NodCarte* rezultat = NULL;
	int* noduriVizitate = initializareNoduriVizitate(graf);
	NodCoada *primul = NULL, *ultimul = NULL;
	pushCoada(primul, ultimul, idNodStart);
	noduriVizitate[idNodStart] = 1;
	while (primul != NULL) {
		int idNodCurent = popCoada(primul, ultimul);
		NodGraf* nodCurent = cautaNodGrafDupaCheie(graf, idNodCurent);
		rezultat = adaugareNodCarte(rezultat, nodCurent->info);
		NodVecin* cursor = nodCurent->vecini;
		while (cursor != NULL) {
			int idVecin = cursor->info->info.id;
			if (noduriVizitate[idVecin] == 0) {
				pushCoada(primul, ultimul, idVecin);
				noduriVizitate[idVecin] = 1;
			}
			cursor = cursor->next;
		}
	}
	return rezultat;
}

Carte citesteCarteFisier(FILE* fisier) {
	Carte c;
	fscanf_s(fisier, "%d", &c.id);
	fgetc(fisier);
	fgets(c.titlu, 50, fisier);
	strtok(c.titlu, "\n");
	fscanf_s(fisier, "%f", &c.pret);
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

void citesteMuchiiGrafFisier(NodGraf* &graf) {
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

void main() {
	printf("\n========================CITIRE NODURI GRAF===============================\n");
	NodGraf* graf = citesteNodGrafFisier();
	afisarNodGraf(graf);
	printf("\n========================ADAUGARE MUCHII===============================\n");
	citesteMuchiiGrafFisier(graf);
	afisarNodGraf(graf);
	printf("\n==========================PARCURGERE DF=============================\n");
	NodCarte* capDf = parcurgereAdancime(graf, 1);
	afisareNodCarte(capDf);
	printf("\n==========================PARCURGERE BF=============================\n");
	NodCarte* capBf = parcurgereLatime(graf, 1);
	afisareNodCarte(capBf);
}
