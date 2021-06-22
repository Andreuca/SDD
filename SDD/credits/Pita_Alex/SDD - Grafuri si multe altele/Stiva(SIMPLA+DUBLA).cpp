#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Cusca {
	char* nume;
	int nrPapagali;
};

struct nod {
	nod* prev;
	Cusca cusca;
	nod* next;
};

struct StivaSimpla {
	StivaSimpla* next;
	Cusca cusca;
};


struct Stiva {
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
	printf("STIVA DUBLA ------------ Cusca cu numele %s are %d papagali.\n", c.nume, c.nrPapagali);
}

void afisCusca2(Cusca c) {
	printf("STIVA SIMPLA ------------ Cusca cu numele %s are %d papagali.\n", c.nume, c.nrPapagali);
}

Stiva push(Stiva &stiv, Cusca c) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->cusca = c;
	nou->next = stiv.cap;
	nou->prev = NULL;
	if (stiv.cap) {
		stiv.cap->prev = nou;
		stiv.cap = nou;
	}
	else {
		stiv.cap = nou;
		stiv.coada = nou;
	}
	return stiv;
}

Cusca pop(Stiva &stiv) {
	if (stiv.cap) {
		nod* temp = stiv.cap;
		Cusca c = temp->cusca;
		stiv.cap = stiv.cap->next;
		free(temp);
		return c;
	}
	else {
		return creeazaCusca("", 0);
	}
}

StivaSimpla* pushStack(StivaSimpla* s,Cusca c) {
	StivaSimpla* ss= (StivaSimpla*)malloc(sizeof(StivaSimpla));
	ss->cusca = c;
	ss->next = s;
	return ss;
}

Cusca popStack(StivaSimpla* &s) {
	if (s) {
		StivaSimpla* temp = s;
		s = s->next;
		Cusca c = temp->cusca;
		free(temp);
		return c;
	}
	else {
		return creeazaCusca("", 0);
	}
	
}


int isEmptyStack(Stiva stiv) {
	return stiv.cap == NULL;
}
int isEmptySimpleStack(StivaSimpla* s) {
	return s == NULL;
}

void afisStivaDubla(Stiva &stiv) {	
	while (!isEmptyStack(stiv)) {
		Cusca c = pop(stiv);	
		afisCusca(c);
		free(c.nume);
		
	}
}

void afisStivaSimpla(StivaSimpla*& ss){
	while (!isEmptySimpleStack(ss)) {
		Cusca c = popStack(ss);
		afisCusca2(c);
		free(c.nume);
	}
}




void main() {	
	Stiva stiv;
	stiv = push(stiv, creeazaCusca("Sobolanii1!", 50));
	stiv = push(stiv, creeazaCusca("Sobolanii2!", 20));
	stiv = push(stiv, creeazaCusca("Sobolanii3!", 10));
	stiv = push(stiv, creeazaCusca("Sobolanii4!", 11));
	stiv = push(stiv, creeazaCusca("Sobolanii5!", 60));
	stiv = push(stiv, creeazaCusca("Sobolanii6!", 30));
	stiv = push(stiv, creeazaCusca("Sobolanii7!", 70));
	stiv = push(stiv, creeazaCusca("Sobolanii8!", 60));
	afisStivaDubla(stiv);
	afisCusca(pop(stiv));
	printf("-----------------------------------------------------------------------\n");
	StivaSimpla* stiva = NULL;
	stiva = pushStack(stiva, creeazaCusca("Sobolanii1!", 10));
	stiva = pushStack(stiva, creeazaCusca("Sobolanii2!", 20));
	stiva = pushStack(stiva, creeazaCusca("Sobolanii3!", 30));
	stiva = pushStack(stiva, creeazaCusca("Sobolanii4!", 40));
	stiva = pushStack(stiva, creeazaCusca("Sobolanii5!", 50));
	stiva = pushStack(stiva, creeazaCusca("Sobolanii6!", 60));
	stiva = pushStack(stiva, creeazaCusca("Sobolanii7!", 70));
	stiva = pushStack(stiva, creeazaCusca("Sobolanii8!", 80));
	afisStivaSimpla(stiva);
	afisCusca2(popStack(stiva));
}