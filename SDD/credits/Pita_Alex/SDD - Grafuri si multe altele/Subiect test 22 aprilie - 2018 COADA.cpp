#include <stdio.h>
#include <string.h>
#include <malloc.h>



struct Comanda {
	int cod;
	char* nume;
	int nrProd;
	float suma; 
};


struct nod {
	nod* next;
	Comanda com;
};

struct Coada {
	nod* cap = NULL;
	nod* final = NULL;
};

Comanda creeazaComanda(int cod, const char* nume, int nrProd, float suma) {
	Comanda c;
	c.cod = cod;
	if (nume) c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy_s(c.nume, strlen(nume) + 1, nume);
	c.nrProd = nrProd;
	c.suma = suma;
	return c;
}

void afisComanda(Comanda c) {
	printf("%d. Comanda pe numele %s are %d produse si are valoare totala de %4.2f !\n", c.cod, c.nume, c.nrProd, c.suma);
}

Coada inserareInCoada(Coada &coada, Comanda com) {
	nod* nodNou = (nod*)malloc(sizeof(nod));
	nodNou->com = com;
	if (!coada.final) coada.final = nodNou;
	if (coada.cap) {
		coada.cap->next = nodNou;
		coada.cap = nodNou;
		coada.cap->next = NULL;
	}
	else coada.cap = nodNou;
	return coada;
	
}
Comanda extragereDinCoada(Coada& coada) {
	if (coada.final) {
		Comanda c = coada.final->com;
		if (coada.final != coada.cap) {
			nod* nou = coada.final;
			coada.final = coada.final->next;
			free(nou);
			
		} else{ 
			free(coada.final);
			coada.final = coada.cap = coada.final->next = NULL;
		}
	return c;
	}
	else{
		creeazaComanda(0, "", 0, 0);
	}
}

int isEmptyQueue(Coada& c) {
	return c.final == NULL;
}

void afisCoada(Coada &c) {
	while (!isEmptyQueue(c)) {
		Comanda com = extragereDinCoada(c);
		afisComanda(com);
		free(com.nume);
	}
}

void afisCoadaFaraExtragere(Coada c) {
	if (c.final) {
		nod* temp = c.final;
		while (temp) {
			Comanda com = temp->com;
			afisComanda(com);
			temp = temp->next;
		}
	}
	else printf("COADA GOALA!\n");
}






//fara 4 ca nu mai aveam chef




void main() {
	Coada coada;
	coada = inserareInCoada(coada, creeazaComanda(1, "IONESCU1", 10, 1000));
	coada = inserareInCoada(coada, creeazaComanda(2, "IONESCU2", 11, 2000));
	coada = inserareInCoada(coada, creeazaComanda(3, "IONESCU3", 12, 3000));
	coada = inserareInCoada(coada, creeazaComanda(4, "IONESCU4", 13, 4000));
	coada = inserareInCoada(coada, creeazaComanda(5, "IONESCU5", 14, 5000));
	coada = inserareInCoada(coada, creeazaComanda(6, "IONESCU6", 15, 6000));
	afisCoadaFaraExtragere(coada);
	printf("-------------------------------\n");
	Comanda c = extragereDinCoada(coada);
	afisComanda(c);
	printf("-------------------------------\n");
	afisCoada(coada);
	afisCoadaFaraExtragere(coada);

}