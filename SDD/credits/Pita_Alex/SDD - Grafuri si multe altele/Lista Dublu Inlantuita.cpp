#include <stdio.h>
#include <string.h>
#include<malloc.h>
#include<conio.h>



//lista dublu inlantuita

struct Cusca {
	char* nume;
	int nrPapagali;
};

struct nod {
	nod* prev;
	Cusca cusca;
	nod* next;
};

struct ListaDubla {
	nod* cap = NULL;
	nod* coada = NULL;
};

Cusca creeazaCusca(const char* nume, int nrPapagali) {
	Cusca c;
	if (nume != NULL)
		c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy_s(c.nume, strlen(nume) + 1, nume);
	c.nrPapagali = nrPapagali;
	return c;
}

void afisCusca(Cusca c) {
	printf("Cusca cu numele %s are %d papagali.\n", c.nume, c.nrPapagali);
}

nod* creeazaNod(nod* prev, Cusca c, nod* next) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->cusca = c;
	nou->prev = prev;
	nou->next = next;
	return nou;
}
ListaDubla inserareInceput(ListaDubla ldi, Cusca c) {
	nod* nou = creeazaNod(NULL, c, ldi.cap);
	if (ldi.cap) {
		ldi.cap->prev = nou;
		ldi.cap = nou;
	}
	else {
		ldi.cap = nou;
		ldi.coada = nou;
	}
	return ldi;
}

ListaDubla inserareFinal(ListaDubla ldi, Cusca c) {
	nod *nou = creeazaNod(ldi.coada, c, NULL);
	if (ldi.coada) {
		ldi.coada->next = nou;
		ldi.coada = nou;
	}
	else {
		ldi.coada = nou;
		ldi.cap = nou;
	}
	return ldi;
}

void afisLista(ListaDubla ldi) {
	if (ldi.cap) {
		nod* temp = ldi.cap;
		while (temp) {
			afisCusca(temp->cusca);
			temp = temp->next;
		}
	}
	else {
		printf("Nu exista lista!");
	}

}

void stergeLista(ListaDubla &ldi) {
	while (ldi.cap) {
		nod* temp = ldi.cap;
		ldi.cap = ldi.cap->next;
		free(temp->cusca.nume);
		free(temp);
	}
	ldi.coada = NULL;

}

ListaDubla sortare(ListaDubla &ldi) {
	Cusca temp;
	if (ldi.cap) {
		for (nod* i = ldi.cap; i->next != NULL; i = i->next)
			for (nod* j = i->next; j != NULL; j = j->next) {
				if (i->cusca.nrPapagali > j->cusca.nrPapagali) {
					temp = i->cusca;
					i->cusca = j->cusca;
					j->cusca = temp;
				}
			}
	}
	return ldi;
}

ListaDubla sortareBubble(ListaDubla &ldi) {

	if (ldi.cap) {

		bool ok = 1;
		nod *t, *q, *s, *r;

		while (ok)
		{
			ok = 0;
			t = ldi.cap;
			while (t && t->next) {
				if (t->cusca.nrPapagali > t->next->cusca.nrPapagali) {
					if (t == ldi.cap) {
						r = t->next;
						s = r->next;

						t->next = s;
						if (s)s->prev = t;
						else ldi.coada = t;

						r->next = t;
						t->prev = r;
						r->prev = NULL;
						ldi.cap = r;
					}
					else {
						q = t->prev;
						r = t->next;
						s = r->next;

						t->next = s;
						if (s)s->prev = t;
						else ldi.coada = t;

						r->next = t;
						t->prev = r;
						r->prev = q;
						q->next = r;
					}
					ok = 1;
				}
				t = t->next;
			}
		}
	}
	return ldi;
}

Cusca extragereNod(ListaDubla& ldi, const char* nume) {
	if (ldi.cap) {
		nod* t = ldi.cap;

		while (t && strcmp(t->cusca.nume, nume) != 0) {
			t = t->next;
		}

		if (t) {
			Cusca c = t->cusca;
			if (t->prev) {
				t->prev->next = t->next;
				if (t->next) {
					t->next->prev = t->prev;
				}
				else {
					ldi.coada = t->prev;
				}
			}
			else {
				ldi.cap = t->next;
				t->next->prev= NULL;
			}
			free(t);
			return c;
		}
		else {
			creeazaCusca("", 0);
		}
	}
}

void main() {
	ListaDubla ldi;
	ldi = inserareInceput(ldi, creeazaCusca("Frumuseii1", 5));
	ldi = inserareInceput(ldi, creeazaCusca("Frumuseii2", 2));
	ldi = inserareInceput(ldi, creeazaCusca("Frumuseii3", 3));
	ldi = inserareInceput(ldi, creeazaCusca("Frumuseii4", 12));
	ldi = inserareInceput(ldi, creeazaCusca("Frumuseii2", 7));
	ldi = inserareInceput(ldi, creeazaCusca("Frumuseii5", 2));
	//ldi = sortareBubble(ldi);
	afisLista(ldi);
	printf("--------------------------------------------------------\n");
	afisCusca(extragereNod(ldi, "Frumuseii2"));
	stergeLista(ldi);
	_getch();
}