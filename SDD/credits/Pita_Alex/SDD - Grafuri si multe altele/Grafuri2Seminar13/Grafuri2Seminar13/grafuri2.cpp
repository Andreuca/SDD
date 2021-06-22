#include <stdio.h>
#include <string.h>
#include <malloc.h>


struct Facultate {
	int id;
	char* nume;
};

struct nodListaPrincpala;

struct nodListaSecundara {
	nodListaSecundara* next;
	//sa putem sa legam lista secundara de cea princapala
	nodListaPrincpala* info;
};

struct nodListaPrincpala {
	nodListaSecundara* vecini;
	Facultate info;
	nodListaPrincpala* next;
};
//inserare la final
nodListaPrincpala* inserareListaPrincipala(nodListaPrincpala* cap, Facultate f) {
	nodListaPrincpala* nou = (nodListaPrincpala*)malloc(sizeof(nodListaPrincpala));
	nou->info = f;
	nou->vecini = NULL;
	nou->next = NULL;
	if (cap) {
		nodListaPrincpala* p = cap;
		while (p->next)
			p = p->next;
		p->next = nou;
		return cap;
	}
	else { return nou; }
}
//inserare la final
nodListaSecundara* inserareListaSecundara(nodListaSecundara* cap, nodListaPrincpala* nod) {
	nodListaSecundara* nou = (nodListaSecundara*)malloc(sizeof(nodListaSecundara));
	nou->next = NULL;
	nou->info = nod;
	if (cap) {
		nodListaSecundara* p = cap;
		while (p->next)
			p = p->next;
		p->next = nou;
		return cap;
	}
	else return nou;
}

nodListaPrincpala* cautareDupaId(nodListaPrincpala* cap, int id) {
	while (cap && cap->info.id != id) {
		cap = cap->next;
	}
	return cap;
}

void inserareArcInGraf(nodListaPrincpala* graf, int idStart, int idStop) {
	if (graf) {
		nodListaPrincpala* nodStart = cautareDupaId(graf, idStart);
		nodListaPrincpala* nodStop = cautareDupaId(graf, idStop);
		if (nodStart && nodStop) {
			nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
			nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);
		}
	}
}

void afisareListaSecundara(nodListaSecundara* cap) {
	while (cap) {
		printf("   %d.%s\n", cap->info->info.id, cap->info->info.nume);
		cap = cap->next;
	}
}

void afisareListaPrincapal(nodListaPrincpala* cap) {
	while (cap) {
		printf("   %d.%s\n", cap->info.id, cap->info.nume);
		printf("VECINI: --------------\n");
		afisareListaSecundara(cap->vecini);
		printf("\n");
		cap = cap->next;
	}
}

struct nodStiva {
	int id;
	nodStiva* next;
};

nodStiva* push(nodStiva* cap, int id) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->next = cap;
	nou->id = id;
	return nou;
}

int pop(nodStiva*& cap) {
	if (cap) {
		int id = cap->id;
		nodStiva* temp = cap;
		cap = cap->next;
		free(temp);
		return id;
	}
	else return -1;
}

int calculareNumarNoduri(nodListaPrincpala* graf) {

	int contor = 0;
	if (graf) {
		contor++;
		graf = graf->next;
	}
	return contor;

}

void parcurgereAdacime(nodListaPrincpala* graf, int idNodStart) {
	if (graf) {
		//1. declaram o stiva si un vector de vizitati
		nodStiva* stiva = NULL;
		int nrNod = calculareNumarNoduri(graf);
		int* vizitate = (int*)malloc(sizeof(int)*nrNod);
		for (int i = 0; i < nrNod; i++)
			vizitate[i] = 0;
		//2. inseram nodul il stiva si-l vizitam
		stiva = push(stiva, idNodStart);
		vizitate[idNodStart] = 1;
		//3. extragem din stiva un nod
		while (stiva) {
			int idNodCurent = pop(stiva);
			nodListaPrincpala* nodCurent = cautareDupaId(graf, idNodCurent);
			//4. afisam nodul curent
			printf(" %d. %s\n", nodCurent->info.id, nodCurent->info.nume);
			//5. inseram in stiva nodurile adiacente nevizitate si le vizitam
			if (nodCurent) {
				nodListaSecundara* p = nodCurent->vecini;
				//crapa aici --------------------------------------------------
				while (p) {
					if (vizitate[p->info->info.id] == 0) {
						stiva = push(stiva, p->info->info.id);
						vizitate[p->info->info.id] = 1;
					}
					p = p->next;
				}
				//---------------------------------------------------------------
			}
		}

		//6. revenim la pasul 3 -- pana cand nu mai avem stiva de noduri
	}
}


//SEMINAR 13

struct nodListaFacultate {
	Facultate info;
	nodListaFacultate* next;
};

void inserareInListaFac(nodListaFacultate*&cap, Facultate f)
{
	nodListaFacultate* nou = (nodListaFacultate*)malloc(sizeof(nodListaFacultate));
	nou->info = f;
	nou->next = cap;
	cap = nou;
}

void inserareInCoada(nodStiva* &cap, int id) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->next = NULL;
	nou->id = id;
	if (cap) {
		nodStiva*  p = cap;
		while (p->next)
			p = p->next;
		p->next = nou;
	}
	else cap = nou;
	
}

nodListaFacultate* copiereGrafInLista(int** matrice, int nrNoduri, Facultate* f, int nodStart) {
	//pentru latime declaram o coada
	nodStiva* coada = NULL;
	int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
		vizitate[i] = 0;
	//inseram in coada
	inserareInCoada(coada, nodStart);
	vizitate[nodStart] = 1;
	nodListaFacultate* listaFacultati = NULL;
	while (coada) {
		int idCurent = pop(coada);
		Facultate f2;
		f2.id = f[idCurent].id;
		f2.nume = (char*)malloc(sizeof(char)*strlen(f[idCurent].nume) + 1);
		strcpy(f2.nume, f[idCurent].nume);
		inserareInListaFac(listaFacultati,f2);
		//verificam 1 in matrice si verificam daca se afla in vizitate
		for (int i = 0; i < nrNoduri; i++) {
			if (matrice[idCurent][i] == 1 && vizitate[i] == 0) {
				vizitate[i] = 1;
				inserareInCoada(coada, i);
			}
		}

	}
	return listaFacultati;
}


void citesteGrafMatrice(int** &matrice, int &nrNoduri, Facultate* &facultati) {
	nrNoduri = 0;
	printf("nr Noduri:");
	scanf("%d", &nrNoduri);
	facultati = (Facultate*)malloc(sizeof(Facultate)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		printf("Id fac:");
		scanf("%d", &facultati[i].id);
		printf("Nume fac:");
		char buffer[20];
		scanf("%s", buffer);
		facultati[i].nume = (char*)malloc(sizeof(char)*strlen(buffer) + 1);
		strcpy(facultati[i].nume, buffer);
	}

	 matrice = (int**)malloc(sizeof(int)*nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		matrice[i] = (int*)malloc(sizeof(int)*nrNoduri);
		for (int j = 0; j < nrNoduri; j++)
			matrice[i][j] = 0;
	}
	int nrarce;
	printf("Nr arce:");
	scanf("%d", &nrarce);
	for (int i = 0; i < nrarce; i++) {
		int idStart = 0;
		printf("Id-ul nodului de start:");
		scanf("%d", &idStart);
		printf("Id-ul nodului de stop:");
		int idStop = 0;
		scanf("%d", &idStop);
		matrice[idStart][idStop] = 1;

	}
}

void afisareCoadaFacultati(nodListaFacultate* cap) {

	if (cap) {
		afisareCoadaFacultati(cap->next);
		printf("%d. %s \n", cap->info.id, cap->info.nume);
		
	}
}

void main() {
	int **matrice;
	Facultate* facultati;
	int nrNoduri;
	citesteGrafMatrice(matrice, nrNoduri, facultati);
	nodListaFacultate* cap = copiereGrafInLista(matrice, nrNoduri, facultati, 1);
	afisareCoadaFacultati(cap);
}