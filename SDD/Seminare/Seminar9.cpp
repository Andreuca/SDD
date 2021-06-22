#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Carte {
	int isbn;
	float pret;
};

struct NodArb {
	Carte info;
	NodArb* stanga;
	NodArb* dreapta;
	int ge;
};

//=============================================== METODE CARTE =============================
Carte citire_carte() {
	Carte c;
	printf("\nISBN: ");
	scanf_s("%d", &c.isbn);
	printf("\nPret: ");
	scanf_s("%f", &c.pret);
	return c;
}

void afisare_carte(Carte c) {
	printf("\nISBN: %d Pret: %2.2f", c.isbn, c.pret);
}

//============================================= METODE AVL ====================================
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
			:rotire_stanga_dreapta(radacina);
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
		if (radacina->info.isbn > carte.isbn) {
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


void stergere_nod_radacina(NodArb* &radacina)
{
	NodArb* nod = radacina;
	if (nod->dreapta)
	{
	
		radacina = nod->dreapta;
		if (nod->stanga)
		{
			NodArb* temp = nod->dreapta;
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

void sterge_nod(NodArb* &radacina, int isbn) {
	if (radacina) {
		if (radacina->info.isbn == isbn) {
			stergere_nod_radacina(radacina);
		}
		else {
			NodArb * nodCurent = radacina;
			if (isbn < nodCurent->info.isbn) {
				sterge_nod(nodCurent->stanga, isbn);
			}
			else {
				sterge_nod(nodCurent->dreapta, isbn);
			}
		}
		radacina = echilibrare(radacina);
	}
}
void main() {
	int ok = 1;
	NodArb* radacina = NULL;
	while (ok == 1) {
		Carte c = citire_carte();
		radacina = inserare_nod(c, radacina);
		printf("\nDoriti sa continuare? Da-1 Nu-0");
		scanf_s("%d", &ok);
	}
	printf("\nAfisare AVL:\n");
	afisare(radacina);
	printf("\nStergere nod cu ISBN: ");
	int isbn;
	scanf_s("%d", &isbn);
	sterge_nod(radacina, isbn);
	printf("\nAfisare AVL:\n");
	afisare(radacina);
}