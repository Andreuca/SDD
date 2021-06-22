#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Cusca {
	char* nume;
	int nrPapagali;
};

struct nodDublu {
	nodDublu* prev;
	Cusca cusca;
	nodDublu* next;
};

struct CoadaSimpla {
	CoadaSimpla* next;
	Cusca cusca;
};

struct CoadaSimpla2 {
	CoadaSimpla* cap = NULL;
	CoadaSimpla* coada = NULL;
};

struct CoadaDubla {
	nodDublu* cap = NULL;
	nodDublu* coada = NULL;
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
	printf("COADA DUBLA ------------ Cusca cu numele %s are %d papagali.\n", c.nume, c.nrPapagali);
}

CoadaDubla inserareQueue(CoadaDubla& cd, Cusca c) {
	nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
	nou->cusca = c;
	nou->next = cd.cap;
	nou->prev = NULL;
	if (cd.cap) {
		cd.cap->prev = nou;
		cd.cap = nou;
	}
	else {
		cd.cap = nou;
		cd.coada = nou;
	}

	return cd;
	
}

Cusca popQueue(CoadaDubla &cd) {
	if (cd.coada) {
		Cusca c = cd.coada->cusca;
		if (cd.cap != cd.coada) {
			cd.coada = cd.coada->prev;
			free(cd.coada->next);
			cd.coada->next = NULL;
		}
		else {
			free(cd.coada);
			cd.coada = cd.cap = NULL;
		}
		return c;
	}
	else {
		creeazaCusca("", 0);
	}
}
int isEmptyQueue(CoadaDubla c) {

	return c.cap == NULL;
}

void afisCoadaDubla(CoadaDubla& c) {
	while (!isEmptyQueue(c)) {
		Cusca cusca=popQueue(c);
		afisCusca(cusca);
		free(cusca.nume);
	}
}



void afisCusca2(Cusca c) {
	printf("COADA SIMPLA ------------ Cusca cu numele %s are %d papagali.\n", c.nume, c.nrPapagali);
}

CoadaSimpla2 inserareCoada(CoadaSimpla2 &cs, Cusca c) {
	CoadaSimpla* csnou = (CoadaSimpla*)malloc(sizeof(CoadaSimpla));
	csnou->cusca = c;
	if (!cs.coada) cs.coada = csnou;
	if (cs.cap) {
		cs.cap->next = csnou;
		cs.cap = csnou;
	}
	else cs.cap = csnou;
	
		return cs;
}

Cusca popCoada(CoadaSimpla2 &cs) {
	
	if (cs.coada) {
		Cusca c = cs.coada->cusca;
		if (cs.coada != cs.cap) {
			CoadaSimpla* aux = cs.coada;
			cs.coada = cs.coada->next;
			free(aux);
		}
		else {
			free(cs.coada);
			cs.coada = cs.cap = NULL;
		}
		return c;
	}
	else 
		return creeazaCusca("", 0);	
}

int isEmptySimpleQueue(CoadaSimpla2 &cs) {
	return cs.coada == NULL;
}

void afisCoadaSimpla(CoadaSimpla2 &cs) {
	while(!isEmptySimpleQueue(cs)) {
		Cusca c = popCoada(cs);
		afisCusca2(c);
		free(c.nume);
	}
}

void main() {
	CoadaSimpla2 cs;
	cs = inserareCoada(cs, creeazaCusca("SOBOLANII1", 50));
	cs = inserareCoada(cs, creeazaCusca("SOBOLANII2", 60));
	cs = inserareCoada(cs, creeazaCusca("SOBOLANII3", 70));
	cs = inserareCoada(cs, creeazaCusca("SOBOLANII4", 80));
	cs = inserareCoada(cs, creeazaCusca("SOBOLANII5", 90));
	cs = inserareCoada(cs, creeazaCusca("SOBOLANII6", 100));
	afisCoadaSimpla(cs);
	printf("--------------------------------------------------------\n");
	CoadaDubla cd;
	cd = inserareQueue(cd, creeazaCusca("SOBOLANII1", 50));
	cd = inserareQueue(cd, creeazaCusca("SOBOLANII2", 60));
	cd = inserareQueue(cd, creeazaCusca("SOBOLANII3", 70));
	cd = inserareQueue(cd, creeazaCusca("SOBOLANII4", 80));
	cd = inserareQueue(cd, creeazaCusca("SOBOLANII5", 90));
	cd = inserareQueue(cd, creeazaCusca("SOBOLANII6", 100));
	afisCoadaDubla(cd);
}