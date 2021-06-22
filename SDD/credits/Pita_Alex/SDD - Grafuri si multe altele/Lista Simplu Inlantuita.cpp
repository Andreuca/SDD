#include <stdlib.h>
#include <stdio.h>
#include <string>

//lista simplu inlatuita-se parcurge intr-un singur sens si contine informatii despre obiect si adresa urm obiect


struct Ferma {
	int numarAnimale;
	char* denumire;
};

struct nod {
	nod* next;
	Ferma info;
};

Ferma createFerma(const char* _denumire, int _nranimale) {

	Ferma f;
	f.denumire = (char*)malloc(sizeof(char)*(strlen(_denumire) + 1));
	strcpy(f.denumire, _denumire);
	f.numarAnimale = _nranimale;
	return f;
}

//returnam nod* ca vrem sa stim adresa unui nod
nod* createNod(Ferma f, nod* next) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = f;
	nou->next = next;
	return nou;
}

//inserare la final

nod* inserareSfarsit(nod* cap, Ferma f) {
	nod* nou = createNod(f, NULL);
	//luam un nod temporar ca sa mergem pana la final
	if (cap)
	{
		nod* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		cap = nou;
	}
	return cap;
}

//inserare la inceput
nod* inserareInceput(nod* cap, Ferma f) {
	nod* nou = createNod(f, cap);
	return nou;
}


void afisareFerma(Ferma f) {
	printf("Numele fermei: %s ---- Numar animale: %d\n", f.denumire, f.numarAnimale);

}
void afisareListaFerme(nod* cap) {
	while (cap) {
		afisareFerma(cap->info);
		cap = cap->next;
	}

	//cu for
	/*
	for(;cap!=NULL;cap=cap->next)
	afisare(cap->info);
	*/
}

//functie ce calculeaz numarul mediu de animale
float medieAnimale(nod* cap) {
	if (cap) {
		int nr = 0, s = 0;
		while (cap) {
			nr++;
			s += cap->info.numarAnimale;
			cap = cap->next;
		}
		return s / nr;
	}
	else return 0;
}

nod* dezalocareCapCoada(nod* cap) {
	while (cap) {
		nod* aux = cap;
		cap = cap->next;
		free(aux->info.denumire);
		free(aux);
	}
	return cap;
}
//inseram o ferma inaintea unei ferme(daca au acelasi nume o alegem pe cea cu nr de animale cel mai mare)
nod* inserareInainteNod(nod* cap, const char* nume, Ferma f) {
	nod* nou = createNod(f, NULL);
	if (cap) {
		nod* temp = cap;
		//noi vrem sa retinem adresa nodului de dinaintea nodului cu cele mai multe animale
		nod* max = cap;
		while (temp && temp->next) {
			if (strcmp(temp->next->info.denumire, nume) == 0) {
				if (temp->next->info.numarAnimale >= max->next->info.numarAnimale)
					max = temp;
			}
			temp = temp->next;
		}
		if (max == cap) {
			if (strcmp(cap->info.denumire, nume) == 0) {
				inserareInceput(cap, f);
			}
			else {
				inserareSfarsit(cap, f);
			}
		}
		else {
			nou->next = max->next;
			max->next = nou;
		}
	}

	else {
		cap = nou;
	}
	return cap;
}

void dezalocareCoadaCap(nod* *cap) {
	//facuta prin recursivitate
	if (*cap != NULL) {
		dezalocareCoadaCap(&(*cap)->next);
		free((*cap)->info.denumire);
		free(*cap);
		*cap = NULL;
	}
}
void main() {
	Ferma f = createFerma("Ferma lui Gigel", 5);
	nod* node = createNod(f, NULL);//un nod care tine informaiti doar despre ferma
	nod* cap = NULL; //lista noua care e goala
					 //inserare elemente in lista
	cap = inserareSfarsit(cap, createFerma("Cocoseii", 1000));
	cap = inserareSfarsit(cap, createFerma("Cocosoul vesel", 700));
	cap = inserareSfarsit(cap, createFerma("Vaca vesela", 500));
	cap = inserareSfarsit(cap, createFerma("No secure", 1200));
	afisareListaFerme(cap);
	cap = inserareInceput(cap, createFerma("Ferma inceput", 1300));
	cap = inserareInceput(cap, createFerma("Zboara puiule", 200));
	printf("\n----------------------------------------------------\nnb");
	afisareListaFerme(cap);
	float medie = medieAnimale(cap);
	printf("Media animalelor fermelor este %4.2f\n", medie);
	cap = inserareInceput(cap, createFerma("Ferma", 50));
	cap = inserareSfarsit(cap, createFerma("No secure", 2200));
	cap = inserareSfarsit(cap, createFerma("No secure", 400));
	printf("\n----------------------------------------------------\n");
	cap = inserareInainteNod(cap, "No secure", createFerma("Ferma", 600));
	afisareListaFerme(cap);
}