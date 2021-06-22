#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct ApelUrgenta {
	int cod;
	int prioritate;
	char adresa[100];
};

struct BinaryTree {
	ApelUrgenta info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};

//==================================== GESTIONARE FISIER =========================================

ApelUrgenta citire_apel_urgenta_fisier(FILE* fisier) {
	ApelUrgenta apel;
	fscanf_s(fisier, "%d", &apel.cod);
	fscanf_s(fisier, "%d", &apel.prioritate);
	fgetc(fisier);
	fgets(apel.adresa, 100, fisier);
	strtok(apel.adresa, "\n");
	return apel;
}

ApelUrgenta citire_apel_urgenta_consola() {
	ApelUrgenta apel;
	printf("\nCod: ");
	scanf_s("%d", &apel.cod);
	printf("\nPrioritate: ");
	scanf_s("%d", &apel.prioritate);
	getc(stdin);
	printf("\nAdresa: ");
	gets_s(apel.adresa, 100);
	return apel;
}

void afisare_apel_urgenta(ApelUrgenta apel) {
	printf("\nCod: %d Prioritate: %d Adresa: %s", apel.cod, apel.prioritate, apel.adresa);
}

ApelUrgenta* citire_apeluri_urgenta_fisier(int &nr) {
	ApelUrgenta* apeluri = NULL;
	FILE* fisier;
	fopen_s(&fisier, "apeluri_urgenta.txt", "r");
	if (fisier != NULL) {
		fscanf_s(fisier, "%d", &nr);
		apeluri = (ApelUrgenta*)malloc(sizeof(ApelUrgenta)*nr);
		for (int i = 0; i < nr; i++) {
			apeluri[i] = citire_apel_urgenta_fisier(fisier);
		}
		fclose(fisier);
	}
	else {
		printf("\nFisierul nu s-a putut deschide");
	}
	return apeluri;
}

void afisare_apeluri_urgenta(ApelUrgenta* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_apel_urgenta(apeluri[i]);
	}
}

//==================================== GESTIONARE BINARY TREE =========================================

BinaryTree* creare_nod(ApelUrgenta apel, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nod = (BinaryTree*)malloc(sizeof(BinaryTree));
	nod->info = apel;
	nod->dreapta = dreapta;
	nod->stanga = stanga;
	return nod;
}

BinaryTree* inserare_nod(ApelUrgenta apel, BinaryTree* radacina) {
	if (radacina) {
		if (radacina->info.cod > apel.cod) {
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

void stergere_nod_radacina(BinaryTree* &radacina)
{
	BinaryTree* nod = radacina;
	if (nod->dreapta)
	{
		radacina = nod->dreapta;
		if (nod->stanga)
		{
			BinaryTree* temp = nod->dreapta;
			while (temp->stanga != NULL) temp = temp->stanga;
			temp->stanga = nod->stanga;
		}
	}
	else if (nod->stanga != NULL) {
		radacina = nod->stanga;
	}
	else {
		radacina = NULL;
	}
	free(nod);
}

void sterge_nod(BinaryTree* &radacina, int cod) {
	if (radacina != NULL) {
		if (radacina->info.cod == cod) {
			stergere_nod_radacina(radacina);
		}
		else {
			BinaryTree * nodCurent = radacina;
			if (cod < nodCurent->info.cod) {
				sterge_nod(nodCurent->stanga, cod);
			}
			else {
				sterge_nod(nodCurent->dreapta, cod);
			}
		}
	}
}

ApelUrgenta cautare_cod(BinaryTree* radacina, int cod) {
	if (radacina != NULL) {
		if (radacina->info.cod == cod) {
			return radacina->info;
		}
		else if (radacina->info.cod > cod) {
			cautare_cod(radacina->stanga, cod);
		}
		else {
			cautare_cod(radacina->dreapta, cod);
		}
	}
	else {
		ApelUrgenta apel;
		apel.cod = -1;
		apel.prioritate = -1;
		return apel;
	}
}
void numara(BinaryTree* radacina, int &nr)
{
	if (radacina != NULL)
	{
		numara(radacina->stanga, nr);
		nr++;
		numara(radacina->dreapta, nr);
	}
}

void afisare_preordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_apel_urgenta(radacina->info);
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
	}
}


void afisare_inordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_preordine(radacina->stanga);
		afisare_apel_urgenta(radacina->info);
		afisare_preordine(radacina->dreapta);
	}
}


void afisare_postordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
		afisare_apel_urgenta(radacina->info);
	}
}

int inaltime_arbore(BinaryTree* radacina) {
	if (radacina) {
		int inaltime_stanga = inaltime_arbore(radacina->stanga);
		int inaltime_dreapta = inaltime_arbore(radacina->dreapta);
		return 1 + (inaltime_stanga > inaltime_dreapta ? inaltime_stanga : inaltime_dreapta);
	}
	else {
		return 0;
	}
}

void afisare_pe_nivel(BinaryTree* radacina, int nivelCautat, int nivelCurent) {
	if (radacina) {
		if (nivelCautat == nivelCurent) {
			afisare_apel_urgenta(radacina->info);
		}
		else {
			afisare_pe_nivel(radacina->stanga, nivelCautat, nivelCurent + 1);
			afisare_pe_nivel(radacina->dreapta, nivelCautat, nivelCurent + 1);
		}
	}
}

void dezalocare(BinaryTree* &radacina) {
	if (radacina) {
		dezalocare(radacina->dreapta);
		dezalocare(radacina->stanga);
		free(radacina);
		radacina = NULL;
	}
}
void main() {
	int nr;
	ApelUrgenta* apeluri = citire_apeluri_urgenta_fisier(nr);
	BinaryTree* radacina = NULL;
	for (int i = 0; i < nr; i++) {
		radacina = inserare_nod(apeluri[i], radacina);
	}
	afisare_preordine(radacina);
	int cod = 0;
	printf("\nIntroducere cod pentru stergere: ");
	scanf_s("%d", &cod);
	sterge_nod(radacina, cod);
	afisare_preordine(radacina);
	dezalocare(radacina);
}