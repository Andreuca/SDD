#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Moneda {
	char* cod;
	char* denumire;
	char* emitent;
	int sold;
};

struct HT {
	Moneda* *vector;
	int dim;
};

Moneda create(const char* cod, const char* denumire, const char* emitent, int sold) {
	Moneda m;
	m.cod = (char*)malloc(strlen(cod) + 1);
	strcpy_s(m.cod, strlen(cod) + 1, cod);
	m.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(m.denumire, strlen(denumire) + 1, denumire);
	m.emitent=(char*)malloc(strlen(emitent) + 1);
	strcpy_s(m.emitent, strlen(emitent) + 1, emitent);
	m.sold = sold;
	return m;
}

void monAfis(Moneda m) {
	printf("%s  , %s  , %s  , %d \n", m.cod, m.denumire, m.emitent, m.sold);
}

HT init(int dim) {
	HT ht;
	ht.dim = dim;
	ht.vector = (Moneda**)malloc(sizeof(Moneda*)*ht.dim);
	for (int i = 0; i < ht.dim; i++)
		ht.vector[i] = NULL;
	return ht;
}

int hashKey(int dim, const char* cod) {
	int nr = 0;
	for (int i = 0; i < strlen(cod); i++)
		nr += cod[i];
	return nr%dim;
}

int inserare(HT &ht, Moneda* m) {
	if (ht.dim > 0) {
		int key = hashKey(ht.dim, m->cod);
		if (ht.vector[key]) {
			int pozitie = (key + 1) % ht.dim;
			while (ht.vector[pozitie] != NULL && pozitie != key) {
				pozitie = (pozitie + 1) % ht.dim;
			}
			if (pozitie == key) {
				return -1;
			}
		else {
			ht.vector[pozitie] = m;
			return pozitie;
			}
		}
		else {
			ht.vector[key] = m;
			return key;
		}
	}
	else return -2;
}

void afisHT(HT ht) {
	if (ht.dim > 0) {
		for(int i=0;i<ht.dim;i++)
			if (ht.vector[i]) {
				monAfis(*ht.vector[i]);
			}
	}
	else printf("HT GOL!\n");
}

void afisMonede(HT ht,int val) {
	if (ht.dim > 0) {
		for (int i = 0; i < ht.dim; i++)
			if (ht.vector[i] && ht.vector[i]->sold > val)
				monAfis(*ht.vector[i]);
	}
	else printf("\n Nu exista ht!\n");
}

void schimbaSold(HT &ht, int val,const char* cod) {
	int nr = 0;
	if (ht.dim > 0) {
		for (int i = 0; i < ht.dim; i++)
			if (ht.vector[i] && strcmp(ht.vector[i]->cod,cod)==0)
			{
				nr += 1;
				ht.vector[i]->sold = val;
			}
			else nr = 0;
			if (nr) printf("Soldul moenedei cu codul %s a fost schimbat!\n", cod);
			else printf("\nNu au fost gasite monede cu acest cod!\n");
	}
}

void main() {
	HT ht;
	ht = init(5);
	inserare(ht, &create("RON", "Leu romanesc", "BNR", 500000));
	inserare(ht, &create("RON", "Dolar american", "USA", 100000));
	inserare(ht, &create("RON", "Moneda europeana", "EUROPA", 200000));
	inserare(ht, &create("LEVA", "Ban bulgaresc", "Bulgaria", 300000));
	inserare(ht, &create("LIRA", "Lira sterlina", "UK", 400000));
	inserare(ht, &create("LIRA", "Lira sterlina", "UK", 400000));
	afisHT(ht);
	printf("----------------------------------------\n");
	afisMonede(ht, 299999);
	printf("----------------------------------------\n");
	schimbaSold(ht, 600, "RON");
	schimbaSold(ht, 500, "ASDSA");
	printf("----------------------------------------\n");
	afisHT(ht);
}