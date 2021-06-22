#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct AparatElectrocasnic {
	int cod;
	int pret;
	char* nume;
	char* cat;
};

struct BinaryTree {
	AparatElectrocasnic info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};

void afisare_electrocasnic(AparatElectrocasnic apel) {
	printf("\nCod: %d Pret: %d Nume: %s Categorie: %s", apel.cod, apel.pret, apel.nume, apel.cat);
}
void afisare_electrocasnice(AparatElectrocasnic* apeluri, int nr) {
	for (int i = 0; i < nr; i++) {
		afisare_electrocasnic(apeluri[i]);
	}
}


BinaryTree* creare_nod(AparatElectrocasnic apel, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nod = (BinaryTree*)malloc(sizeof(BinaryTree));
	nod->info = apel;
	nod->dreapta = dreapta;
	nod->stanga = stanga;
	return nod;
}

BinaryTree* inserare_nod(AparatElectrocasnic apel, BinaryTree* radacina) {
	if (radacina) {
		if (radacina->info.pret > apel.pret) {
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
		afisare_electrocasnic(radacina->info);
		afisare_preordine(radacina->stanga);
		afisare_preordine(radacina->dreapta);
	}
}
int minPret(BinaryTree* radacina) {
	if (radacina->stanga != NULL) {
		minPret(radacina->stanga);
	}
	else return radacina->info.pret;
}

void nrarb(BinaryTree* radacina,int &nr) {
	if (radacina) {
		nrarb(radacina->stanga,nr);
		nr++;
	}
}
void numara(BinaryTree* radacina, int& nr)
{
	if (radacina != NULL)
	{
		numara(radacina->stanga, nr);
		
		numara(radacina->dreapta, nr);nr++;
	}
}
void stergere_nod_radacina(BinaryTree*& radacina)
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

void sterge_nod(BinaryTree*& radacina, int cod) {
	if (radacina != NULL) {
		if (radacina->info.cod == cod) {
			stergere_nod_radacina(radacina);
		}
		else {
			BinaryTree* nodCurent = radacina;
			if (cod < nodCurent->info.cod) {
				sterge_nod(nodCurent->stanga, cod);
			}
			else {
				sterge_nod(nodCurent->dreapta, cod);
			}
		}
	}
}

void dezalocare(BinaryTree*& radacina);
AparatElectrocasnic maxPret(BinaryTree* radacina) {
	if (radacina->dreapta != NULL) {
		maxPret(radacina->dreapta);
	}
	else {
		AparatElectrocasnic a;
		a.cod = radacina->info.cod;
		a.pret = radacina->info.pret;
		a.nume = (char*)malloc(sizeof(char) * (strlen(radacina->info.nume)));
		a.cat = (char*)malloc(sizeof(char) * (strlen(radacina->info.cat)));
		strcpy(a.nume, radacina->info.nume);
		strcpy(a.cat, radacina->info.cat);
		sterge_nod(radacina,radacina->info.cod);
		//dezalocare(radacina);
	return a;
	}
		
}
void modificaremax(BinaryTree* radacina,int min, BinaryTree* radacinaoriginal) {
	
	if (radacina->dreapta != NULL) {
		modificaremax(radacina->dreapta,min,radacinaoriginal);
	}
	else {
		AparatElectrocasnic a;
		a.cod = radacina->info.cod;
		a.pret = min--;
		a.nume = (char*)malloc(sizeof(char) * (strlen(radacina->info.nume)));
		a.cat = (char*)malloc(sizeof(char) * (strlen(radacina->info.cat)));
		strcpy(a.nume, radacina->info.nume);
		strcpy(a.cat, radacina->info.cat);
		inserare_nod(a, radacinaoriginal);
		sterge_nod(radacina, radacina->info.cod);
		//dezalocare(radacina);
		
	}

}
/////////////////////////////////////////////Cerinta 3//////////////////////////////////////////////////
struct nod {
	AparatElectrocasnic info;
	nod* next;
};

nod* inserare_element(nod* &cap, AparatElectrocasnic info) {
	if (cap == NULL) {
		cap = (nod*)malloc(sizeof(nod));
		//cap->info = info;
		cap->info.cod = info.cod;
		cap->info.pret = info.pret;
		cap->info.nume = (char*)malloc(sizeof(char) * (strlen(info.nume)));
		cap->info.cat = (char*)malloc(sizeof(char) * (strlen(info.cat)));
		strcpy(cap->info.nume, info.nume);
		strcpy(cap->info.cat, info.cat);
		cap->next = NULL;
	}
	else
	{
		nod* cursor = cap;
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->next = NULL;
		//nou->info = info;
		nou->info.cod = info.cod;
		nou->info.pret = info.pret;
		nou->info.nume = (char*)malloc(sizeof(char) * (strlen(info.nume)));
		nou->info.cat = (char*)malloc(sizeof(char) * (strlen(info.cat)));
		strcpy(nou->info.nume, info.nume);
		strcpy(nou->info.cat, info.cat);
		cursor->next = nou;
	}
	return cap;
}
void creare_lista(BinaryTree* radacina, nod* &cap) {
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
		printf("\nCod: %d Pret: %d Nume: %s Categorie: %s", cursor->info.cod, cursor->info.pret, cursor->info.nume, cursor->info.cat);
		cursor = cursor->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
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
	FILE* file = fopen("Aparat.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	AparatElectrocasnic* aparate = (AparatElectrocasnic*)malloc(sizeof(AparatElectrocasnic) * nr);

	while (fgets(buffer, 128, file)) {
		AparatElectrocasnic a;
		token = strtok(buffer, splitter);
		a.cod = atoi(token);

		token = strtok(NULL, splitter);
		a.pret = atoi(token);

		token = strtok(NULL, splitter);
		a.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.nume, token);

		token = strtok(NULL, splitter);
		a.cat = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.cat, token);

		aparate[i++] = a;
	}

	BinaryTree* radacina = NULL;
	for (int i = 0; i < nr; i++) {
		radacina = inserare_nod(aparate[i], radacina);
	}
	afisare_preordine(radacina);

	printf("\n%d\n", minPret(radacina));
	//AparatElectrocasnic aa = maxPret(radacina);
	//afisare_electrocasnic(aa);
	printf("\n++++++++++++++++ ver final ++++++++++++++\n");

	int min = minPret(radacina);
	//modificaremax(radacina, min,radacina);
	int nrn = 0;
	nrarb(radacina, nrn);
	static nod* cap = NULL;
	creare_lista(radacina, cap);
	traversare(cap);
	//afisare_preordine(radacina);
	dezalocare(radacina);
	dezalocarelista(cap);
}

