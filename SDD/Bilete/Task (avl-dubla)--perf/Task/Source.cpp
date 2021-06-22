#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Task {
	int cod;
	int nrTask;
	int nrPagini;
	char* numeTask;
	char* categorie;
};

struct NodArb {
	Task info;
	NodArb* stanga;
	NodArb* dreapta;
	int ge;
};

////////////////////////Cerinta-3//////////////////////////

struct nod {
	Task info;
	nod* next;
	nod* prev;
};
nod* inserare_element(nod*& cap, Task info) {
	if (cap == NULL) {
		cap = (nod*)malloc(sizeof(nod));
		//cap->info = info;
		cap->info.cod = info.cod;
		cap->info.nrTask = info.nrTask;
		cap->info.nrPagini = info.nrPagini;
		cap->info.numeTask = (char*)malloc(sizeof(char) * (strlen(info.numeTask)));
		cap->info.categorie = (char*)malloc(sizeof(char) * (strlen(info.categorie)));
		strcpy(cap->info.numeTask, info.numeTask);
		strcpy(cap->info.categorie, info.categorie);
		cap->next = NULL;
		//DIFERENTA
		cap->prev = NULL;
		
	}
	else
	{
		nod* cursor = cap;
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->next = NULL;
		nou->info.cod = info.cod;
		nou->info.nrTask = info.nrTask;
		nou->info.nrPagini = info.nrPagini;
		nou->info.numeTask = (char*)malloc(sizeof(char) * (strlen(info.numeTask)));
		nou->info.categorie = (char*)malloc(sizeof(char) * (strlen(info.categorie)));
		strcpy(nou->info.numeTask, info.numeTask);
		strcpy(nou->info.categorie, info.categorie);
		cursor->next = nou;

		////DIFERENTA
		nou->prev = cursor;
	}
	return cap;
}
void creare_lista(NodArb* radacina, nod*& cap) {
	if (radacina == NULL) return;
	if (radacina->info.cod < 5) {
		inserare_element(cap, radacina->info);
	}

	creare_lista(radacina->stanga, cap);
	creare_lista(radacina->dreapta, cap);
}

void traversare(nod* cap) {
	printf("\nAfisare lista\n");
	nod* cursor;
	cursor = cap;
	while (cursor) {
		printf("\nCod: %d nrTask: %d nrPagini: %d numeTask: %s categorie: %s", cursor->info.cod, cursor->info.nrTask, cursor->info.nrPagini, cursor->info.numeTask, cursor->info.categorie);
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
////////////////////////////////////////////





void afisare_task(Task c) {
	printf("\nCod: %d nrTask: %d nrPagini: %d numeTask: %s categorie: %s", c.cod, c.nrTask, c.nrPagini, c.numeTask, c.categorie);
}
NodArb* creare_nod(Task c) {
	NodArb* nod = (NodArb*)malloc(sizeof(NodArb));
	nod->dreapta = NULL;
	nod->stanga = NULL;
	nod->ge = 0;
	nod->info = c;
	return nod;
}

void afisare(NodArb* radacina) {
	if (radacina) {
		afisare_task(radacina->info);
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


NodArb* inserare_nod(Task carte, NodArb* radacina) {
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
	FILE* file = fopen("Task.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Task* taskuri = (Task*)malloc(sizeof(Task) * nr);

	while (fgets(buffer, 128, file)) {
		Task a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.nrTask = atoi(token);

		token = strtok(NULL, splitter);
		a.nrPagini = atoi(token);

		token = strtok(NULL, splitter);
		a.numeTask = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.numeTask, token);

		token = strtok(NULL, splitter);
		a.categorie = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.categorie, token);

		taskuri[i++] = a;
	}

	NodArb* radacina = NULL;
	for (int i = 0; i < nr; i++) {
		radacina = inserare_nod(taskuri[i], radacina);
	}
	printf("\n++++++++++++++++ Cerinta 1++++++++++++++\n");
	printf("\nAfisare AVL:\n");
	afisare(radacina);

	printf("\n++++++++++++++++ Cerinta 3++++++++++++++\n");
	static nod* cap = NULL;
	creare_lista(radacina, cap);
	traversare(cap);
}