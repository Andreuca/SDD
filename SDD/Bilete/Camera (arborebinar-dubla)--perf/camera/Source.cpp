#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Camera {
	int cod;
	int pretCamera;
	char* numeCamera;
	char* tipCamera;
};

struct BinaryTree {
	Camera info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};

struct nod {
	Camera info;
	nod* next;
	nod* prev;
};
/////////////////////////////Cerinta 3//////////////////////////////////////
nod* inserare_element(nod*& cap, Camera info) {
	if (cap == NULL) {
		cap = (nod*)malloc(sizeof(nod));
		//cap->info = info;
		cap->info.cod = info.cod;
		cap->info.pretCamera = info.pretCamera;
	
		cap->info.numeCamera = (char*)malloc(sizeof(char) * (strlen(info.numeCamera)));
		cap->info.tipCamera = (char*)malloc(sizeof(char) * (strlen(info.tipCamera)));
		strcpy(cap->info.numeCamera, info.numeCamera);
		strcpy(cap->info.tipCamera, info.tipCamera);
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
		nou->info.pretCamera = info.pretCamera;

		nou->info.numeCamera = (char*)malloc(sizeof(char) * (strlen(info.numeCamera)));
		nou->info.tipCamera = (char*)malloc(sizeof(char) * (strlen(info.tipCamera)));
		strcpy(nou->info.numeCamera, info.numeCamera);
		strcpy(nou->info.tipCamera, info.tipCamera);
		nou->next = NULL;
		cursor->next = nou;

		////DIFERENTA
		nou->prev = cursor;
	}
	return cap;
}
void creare_lista(BinaryTree* radacina, nod*& cap) {
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
		printf("\nCod: %d PretCamera: %d NumeCamera: %s tipCamera: %s", cursor->info.cod, cursor->info.pretCamera, cursor->info.numeCamera, cursor->info.tipCamera);
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


/// ////////////////////////////////////////////
void afisare_apel_urgenta(Camera apel) {
	printf("\nCod: %d PretCamera: %d NumeCamera: %s tipCamera: %s", apel.cod, apel.pretCamera, apel.numeCamera, apel.tipCamera);
}
void afisare_apeluri_urgenta(Camera* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_apel_urgenta(apeluri[i]);
	}
}

BinaryTree* creare_nod(Camera apel, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nod = (BinaryTree*)malloc(sizeof(BinaryTree));
	nod->info = apel;
	nod->dreapta = dreapta;
	nod->stanga = stanga;
	return nod;
}

BinaryTree* inserare_nod(Camera apel, BinaryTree* radacina) {
	if (radacina) {
		if (radacina->info.pretCamera > apel.pretCamera) {
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

void afisare_preordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_apel_urgenta(radacina->info);
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
	}
}



//Dezalocari
void dezalocare(BinaryTree*& radacina) {
	if (radacina) {
		dezalocare(radacina->dreapta);
		dezalocare(radacina->stanga);
		free(radacina);
		radacina = NULL;
	}
}
void dezalocarelista(nod* cap)
{
	nod* temp = cap;
	while (temp != NULL)
	{
		nod* temp2 = temp->next;

		free(temp);
		temp = temp2;
	}
}

int main() {
	FILE* file = fopen("Camera.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Camera* camere = (Camera*)malloc(sizeof(Camera) * nr);

	while (fgets(buffer, 128, file)) {
		Camera a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.pretCamera = atoi(token);

		;

		token = strtok(NULL, splitter);
		a.numeCamera = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.numeCamera, token);

		token = strtok(NULL, splitter);
		a.tipCamera = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.tipCamera, token);

		camere[i++] = a;
	}


	BinaryTree* radacina = NULL;
	for (int i = 0; i < nr; i++) {
		radacina = inserare_nod(camere[i], radacina);
	}
	afisare_preordine(radacina);


	//

	printf("\n\n++++++++++++++++ punctul 3 ++++++++++++++\n");
	static nod* cap = NULL;
	creare_lista(radacina, cap);
	traversare(cap);
	printf("\n\n++++++++++++++++ punctul 4 ++++++++++++++\n");
	//inserare_element_pozitie(cap, camere[1], 5);
	//traversare(cap);

	dezalocare(radacina);
	dezalocarelista(cap);
}