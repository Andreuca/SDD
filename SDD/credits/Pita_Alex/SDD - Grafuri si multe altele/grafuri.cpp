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
	while (cap && cap->info.id!=id) {
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

nodStiva* push(nodStiva* cap,int id) {
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

void parcurgereAdacime(nodListaPrincpala* graf,int idNodStart) {
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

void main() {
	nodListaPrincpala* graf = NULL;
	printf("Nr Noduri:");
	int n = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		//alocam facultati
		Facultate f;
		f.id = i;
		char buffer[20];
		printf("Nume fac:"); scanf("%s", buffer);
		f.nume = (char*)malloc(strlen(buffer));
		strcpy(f.nume, buffer);
		//inseram in fac
		graf = inserareListaPrincipala(graf, f);
	}
	printf("Numar arce:");
	int nrarce = 0;
	scanf("%d", &nrarce);
	for (int i = 0; i < nrarce; i++) {
		int idStart = 0;
		printf("Id-ul nodului de start:");
		scanf("%d", &idStart);
		printf("Id-ul nodului de stop:");
		int idStop = 0;
		scanf("%d", &idStop);
		inserareArcInGraf(graf, idStart, idStop);
	}
	afisareListaPrincapal(graf);
	printf("------------------------------------------------------\n");
	parcurgereAdacime(graf, 4);
}