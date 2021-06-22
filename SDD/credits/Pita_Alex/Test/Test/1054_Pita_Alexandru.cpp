#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#define LINE_SIZE 128
#define DIM 100

struct Magazin {
	int id;
	char* denumire;
	char* localitate;
	float suprafata;
	int numar_angajati;
};

struct Nod {
	Magazin* mag;
	Nod* next;
};

// Inserare nod 
Nod* inserareLista(Nod* lst, Magazin* mag) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->mag = (Magazin*)malloc(sizeof(Magazin));

	nou->mag->id = mag->id;
	nou->mag->denumire = mag->denumire;
	nou->mag->localitate = mag->localitate;
	nou->mag->suprafata = mag->suprafata;
	nou->mag->numar_angajati = mag->numar_angajati;
	nou->next = NULL;

	if (lst == NULL)
		return nou;
	else {
		Nod* temp = lst;
		Nod* prevTemp = temp;
		if (nou->mag->id < prevTemp->mag->id) {
			nou->next = prevTemp;

			return nou;
		}
		else if (temp->next) {
			while (temp->next) {
				temp = temp->next;
				if (nou->mag->id < temp->mag->id) {
					prevTemp->next = nou;
					nou->next = temp;
					
					return lst;
				}
				else if(temp->next == NULL) {
					temp->next = nou;

					return lst;

				}
				prevTemp = temp;
			}
		}
		else {
			if (nou->mag->id < temp->mag->id) {
				nou->next = temp;
				temp->next = NULL;

				return nou;
			}
			else {
				temp->next = nou;
			}
		}
	}

	return lst;
}

void modificareDenumireMagazin(Nod* lst, char* denumire, char* localitate) {
	Nod* temp = lst;
	char ok = 0;
	while (temp) {
		if (!strcmp(temp->mag->denumire, denumire) && !strcmp(temp->mag->localitate,localitate) ) {
			printf("\nIntroduceti un nou nume pentru magazinul \"%s\" din localitatea \"%s\": ", denumire, localitate);
			char buffer[50];
			fgets(buffer, 50, stdin);
			strtok(buffer, "\n");
			strcpy(temp->mag->denumire, buffer);
			ok = 1;
		}

		temp = temp->next;
	}

	if (ok == 0) {
		printf("\nNu s-a gasit magazinul cu denumirea sau localitatea specificata!\n");
	}
}

float determinaNrMediuAngajati(Nod* lst, char* localitate) {
	int angajati = 0;
	float k = 0;
	Nod* temp = lst;
	while (temp) {
		if (!strcmp(temp->mag->localitate, localitate)) {
			angajati += temp->mag->numar_angajati;
			k++;
		}

		temp = temp->next;
	}

	float medie = angajati / k;

	return medie;
}

int functieHash(char* localitate, int size) {
	int temp = 0, poz;
	
	for (int i = 0; i < strlen(localitate); i++)
		temp += localitate[i];

	poz = temp % size;

	return poz;
}

void inserareHTable(Nod** hTab, Magazin* mag, int sizeHT) {
	int k;

	k = functieHash(mag->localitate, sizeHT);

	//int temp = k;
	char ok = 0;
	while (k > -1 && ok != 1) {
		if (hTab[k] == NULL) {
			hTab[k] = (Nod*)malloc(sizeof(Nod));
			hTab[k]->mag = (Magazin*)malloc(sizeof(Magazin));
			hTab[k]->mag->id = mag->id;
			hTab[k]->mag->denumire = (char*)malloc((strlen(mag->denumire) + 1) * sizeof(char));
			strcpy(hTab[k]->mag->denumire, mag->denumire);
			hTab[k]->mag->localitate = (char*)malloc((strlen(mag->localitate) + 1) * sizeof(char));
			strcpy(hTab[k]->mag->localitate, mag->localitate);
			hTab[k]->mag->suprafata = mag->suprafata;
			hTab[k]->mag->numar_angajati = mag->numar_angajati;
			ok = 1;
		}
		k--;
	}

	if (k == -1) {
		printf("\nMagazinul nu a putut fi inserat in tabela de dispersie!\n");
	}

	/*if (k == -1) {
		k = 99;
		while (k > temp && ok != 1) {
			if (hTab[k] == NULL) {
				hTab[k] = inserareLista(hTab[k], mag);
				ok = 1;
			}
			k--;
		}
	}

	if(ok == 0)
		hTab[temp] = inserareLista(hTab[temp], mag);*/
}

void parseHTabel(Nod** hTab, int sizeHT) {
	for (int i = 0; i < sizeHT; i++) {
		if (hTab[i])
			printf("%d, %s, %s, %.3f, %d\n", hTab[i]->mag->id, hTab[i]->mag->denumire, hTab[i]->mag->localitate, hTab[i]->mag->suprafata, hTab[i]->mag->numar_angajati);
	}
}

void modificareLocalitateMagazin(Nod** hTab, int size, char* denumire, char* localitate) {
	int k;
	k = functieHash(localitate, size);

	char ok = 0;
	while (k > -1 && ok != 1) {
		if (hTab[k]) {
			if (!strcmp(hTab[k]->mag->localitate, localitate) && !strcmp(hTab[k]->mag->denumire, denumire)) {
				printf("\nIntroduceti noua localitate a magazinului \"%s\" din localitatea \"%s\" : ", denumire, localitate);
				char buffer[50];
				fgets(buffer, 50, stdin);
				strtok(buffer, "\n");
				strcpy(hTab[k]->mag->localitate, buffer);

				Nod* temp = NULL;
				temp = (Nod*)malloc(sizeof(Nod));
				temp->mag = (Magazin*)malloc(sizeof(Magazin));
				temp->mag->id = hTab[k]->mag->id;
				temp->mag->denumire = (char*)malloc((strlen(hTab[k]->mag->denumire) + 1) * sizeof(char));
				strcpy(temp->mag->denumire, hTab[k]->mag->denumire);
				temp->mag->localitate = (char*)malloc((strlen(hTab[k]->mag->localitate) + 1) * sizeof(char));
				strcpy(temp->mag->localitate, hTab[k]->mag->localitate);
				temp->mag->suprafata = hTab[k]->mag->suprafata;
				temp->mag->numar_angajati = hTab[k]->mag->numar_angajati;
				temp->next = NULL;
				inserareHTable(hTab, temp->mag, size);

				free(hTab[k]->mag->denumire);
				free(hTab[k]->mag->localitate);
				free(hTab[k]->mag);
				free(hTab[k]);

				hTab[k] = NULL;

				ok = 1;
			}
		}
		k--;
	}

	if (k == -1) {
		printf("\nNu s-a gasit magazinul cu denumirea sau localitatea specificata!\n");
	}
}

void stergereLista(Nod* &lst) {
	Nod* temp;
	while (lst->next) {
		temp = lst;
		lst = lst->next;

		free(temp->mag->denumire);
		free(temp->mag->localitate);
		free(temp->mag);
		free(temp);

		temp = NULL;
	}

	free(lst->mag->denumire);
	free(lst->mag->localitate);
	free(lst->mag);
	free(lst);

	lst = NULL;
}

void stergereHTable(Nod** hTab, int size) {
	for (int i = 0; i < size; i++) {
		if (hTab[i]) {
			free(hTab[i]->mag->denumire);
			free(hTab[i]->mag->localitate);
			free(hTab[i]->mag);
			free(hTab[i]);
			
			hTab[i] = NULL;
		}
	}
}

void main() {	
	Nod* lista = NULL;
	Magazin magazin;

	FILE* f;
	f = fopen("Magazine.txt", "r");

	char* token, file_buf[LINE_SIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		magazin.id = atoi(token);

		token = strtok(NULL, sep_list);
		magazin.denumire = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(magazin.denumire, token);

		token = strtok(NULL, sep_list);
		magazin.localitate = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(magazin.localitate, token);

		token = strtok(NULL, sep_list);
		magazin.suprafata = atof(token);

		token = strtok(NULL, sep_list);
		magazin.numar_angajati = atoi(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare!");

		lista = inserareLista(lista, &magazin);

		magazin.denumire = NULL;
		magazin.localitate = NULL;
	}

	printf("\nTraversarea listei simple dupa ce a fost creata:\n");
	Nod* temp = lista;
	while (temp != NULL) {
		printf("%d, %s, %s, %.3f, %d\n", temp->mag->id, temp->mag->denumire, temp->mag->localitate, temp->mag->suprafata, temp->mag->numar_angajati);

		temp = temp->next;
	}

	modificareDenumireMagazin(lista, (char*)"La 2 Pasi", (char*)"Bistrita");
	printf("\nAfisare lista dupa modificare denumire magazin:\n");
	temp = lista;
	while (temp != NULL) {
		printf("%d, %s, %s, %.3f, %d\n", temp->mag->id, temp->mag->denumire, temp->mag->localitate, temp->mag->suprafata, temp->mag->numar_angajati);

		temp = temp->next;
	}

	printf("\nAfisare numar mediu de angajati din localitatea Constanta: %.2f.\n", determinaNrMediuAngajati(lista, (char*)"Constanta"));

	// Tabela de dispersie
	Nod** hTable;
	hTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	for (int i = 0; i < DIM; i++) {
		hTable[i] = NULL;
	}

	temp = lista;
	while (temp) {
		inserareHTable(hTable, temp->mag, DIM);

		temp = temp->next;
	}

	printf("\nAfisare tabela de dispersie:\n");
	parseHTabel(hTable, DIM);

	modificareLocalitateMagazin(hTable, DIM, (char*)"Magazin Alimentar", (char*)"Constanta");
	printf("\nAfisare tabela de dispersie dupa modificare localitate:\n");
	parseHTabel(hTable, DIM);

	// Dezalocare tabela de dispersie
	stergereHTable(hTable, DIM);
	printf("\nAfisare tabela de dispersie dupa dezalocare:\n");
	parseHTabel(hTable, DIM);

	// Dezalocare lista simpla
	stergereLista(lista);

	printf("\nAfisare lista simpla dupa dezalocare:\n");
	temp = lista;
	while (temp != NULL) {
		printf("%d, %s, %s, %.3f, %d\n", temp->mag->id, temp->mag->denumire, temp->mag->localitate, temp->mag->suprafata, temp->mag->numar_angajati);

		temp = temp->next;
	}
}