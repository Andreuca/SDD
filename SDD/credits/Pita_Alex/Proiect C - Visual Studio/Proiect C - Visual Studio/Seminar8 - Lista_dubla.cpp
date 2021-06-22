#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

// Lista simpla
struct NodDublu {
	Student stud; // date propriu-zise
	NodDublu* next;
	NodDublu* prev;
};

struct ListaDubla {
	NodDublu* prim;
	NodDublu* ultim;
};

ListaDubla inserareSfarsitListaDubla(ListaDubla lst, Student s) {
	NodDublu* nou;
	nou = (NodDublu*)malloc(sizeof(NodDublu)); // alocare nod nou
	// nou->stud = s; // copiere inclusiv nrGrupa !!!
	nou->stud.id = s.id;
	nou->stud.nume = s.nume; // asumare s.nume va fi copiat peste nou->nume
	strcpy(nou->stud.nrGrupa, s.nrGrupa);
	nou->next = NULL;
	nou->prev = lst.ultim;

	if (lst.prim == NULL) {// lista nu contine nici un nod/element
		lst.prim = lst.ultim = nou;
	}	
	else {
		// parsare lista pana pe ultimul element
		lst.ultim->next = nou;
		lst.ultim = nou;
	}

	return lst;
}

// interschimb noduri adiacente in lista dubla
ListaDubla interschimbAdiacente(ListaDubla lst, int idStud) {
	NodDublu *p, *q, *r, *s;

	// cazuri particulare
	//		1. lista contine cel mult 1 nod - se abandoneaza operatia
	if (lst.prim == NULL || lst.prim->next == NULL)
		return lst;

	//		2. primul nod din interschimb este lst (se interschimba nodul 1 cu 2) - are loc interschimb, se returneaza noul inceput de lista
	if (lst.prim->stud.id == idStud) {
		// initializam cele 3 noduri implicate in interschimb
		q = lst.prim;	// nodul 1
		r = lst.prim->next;	// nodul 2
		s = r->next;	// nodul 3/NULL

		if (s != NULL) { // r nu este ultimul nod din lista dubla
			q->next = s;
			r->next = q;

			// actualizare predecesori pt nodurile q, r si s
			q->prev = r;
			r->prev = NULL;
			s->prev = q;

			// actualizare inceput de lista dubla
			lst.prim = r;
		}
		else {
			// Caz particular 5: exista 2 noduri in lista dubla care se interschimba
			// se actualizeaza ambele capete de lista dubla
			q->next = s;
			r->next = q;

			// actualizare predecesor DOAR pt nodurile q si r
			q->prev = r;
			r->prev = NULL;

			// actualizare adresa inceput si sfarsit de lista dubla
			lst.prim = r;
			lst.ultim = q;
		}

		return lst;
	}

	//	3. primul nod din interschimb este ultimul din lista (nu exista nodul 2) - se abandoneaza operatia
	//	4. primul nod din interschimb nu este identificat - nu are sens operatia de interschimb
	// caz general

	// traversare lista in vederea identificarii primului nod din interschimb (q)
	p = lst.prim;
	while (p->next) {
		q = p->next;
		if (q->stud.id == idStud) {
			// am identificat primul nod din interschimb
			// caz 3 / caz general
			if (q->next != NULL) {	// daca FALSE -> caz particular 3; q este ultimul nod din lista, nu exista r pt interschimb
				// caz general
				r = q->next;
				s = r->next;

				if (s != NULL) {
					p->next = r;
					r->next = q;
					q->next = s;

					q->prev = r;
					r->prev = p;
					s->prev = q;
				}
				else {
					// Caz particular 6
					// s == NULL,  r este de fapt ultimul nod din lista dubla -> se actualizeaza sfarsitul de lista
					p->next = r;
					r->next = q;
					q->next = s;

					q->prev = r;
					r->prev = p;

					// actualizarea sfarsitului de lista dubla
					lst.ultim = q;
				}
			}

			return lst;
		}

		p = p->next;
	}
	// p->next == NULL -> q == NULL, deci caz particular 4


	return lst;
}

// interschimb noduri oarecare in lista dubla
ListaDubla interschimbNoduriOarecare(ListaDubla ld, int idStud1, int idStud2) {
	if (ld.prim == NULL || ld.prim->next == NULL)
		return ld;

	NodDublu *p, *q, *r, *s;
	p = ld.prim;
	if (p->stud.id == idStud1 || p->stud.id == idStud2) {
		q = p->next;
		while (q) {
			if (q->stud.id == idStud1 || q->stud.id == idStud2) {
				if (p->next == q) {
					return interschimbAdiacente(ld, p->stud.id);
				}
				else {
					r = q->next;

					if (r) {
						NodDublu* prevQ = q->prev;
						q->prev = NULL;
						p->prev = prevQ;
						r->prev = p;

						NodDublu* nextP = p->next;
						prevQ->next = p;
						q->next = nextP;
						p->next = r;

						ld.prim = q;
					}
					else {
						NodDublu* prevQ = q->prev;
						q->prev = NULL;
						p->prev = prevQ;

						NodDublu* nextP = p->next;
						prevQ->next = p;
						q->next = nextP;
						p->next = r;

						ld.prim = q;
						ld.ultim = p;
					}
				}

				return ld;
			}
			q = q->next;
		}
	}

	while (p->next) {
		q = p->next;
		if (q->stud.id == idStud1 || q->stud.id == idStud2) {
			r = q->next;
			while (r) {
				if (r->stud.id == idStud1 || r->stud.id == idStud2) {
					if (q->next == r) {
						return interschimbAdiacente(ld, q->stud.id);
					}
					else {
						s = r->next;

						if (s) {
							NodDublu* prevR = r->prev;
							r->prev = p;
							q->prev = prevR;
							s->prev = q;

							prevR->next = q;
							p->next = r;
							r->next = q->next;
							q->next = s;
						}
						else {
							NodDublu* prevR = r->prev;
							r->prev = p;
							q->prev = prevR;

							prevR->next = q;
							p->next = r;
							r->next = q->next;
							q->next = s;

							ld.ultim = q;
						}
					}

					return ld;
				}
				r = r->next;
			}
		}
		p = p->next;
	}
}

// sortare noduri lista dubla
ListaDubla sortareListaDubla(ListaDubla lista) {
	char vb = 1;

	while (vb == 1) {
		vb = 0;
		NodDublu* temp = lista.prim;
		while (temp->next) {
			NodDublu* temp2 = temp->next;
			if (temp->stud.id > temp2->stud.id) {
				vb = 1;
				lista = interschimbAdiacente(lista, temp->stud.id);
			}
			else {
				temp = temp->next;
			}
		}
	}

	return lista;
}

// implementare QuickSort -> stiva/stive

void main() {
	ListaDubla ld;
	
	ld.prim = ld.ultim = NULL;
	Student s;

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		// alocare (nume) si initializare student
		token = strtok(file_buf, sep_list);
		s.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		s.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(s.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(s.nrGrupa, token);

		token = strtok(NULL, sep_list); // verificare existenta token dupa medie in linia curenta file_buf
		if (token)
			printf("\nEroare preluare token!");
		// apel functie inserare nod in lista dubla
		ld = inserareSfarsitListaDubla(ld, s);

		s.nume = NULL;
	}

	// parsare lista simpla pentru validare inserari
	printf("Traversare lista dubla dupa creare:\n");
	NodDublu* temp = ld.prim;
	while (temp != NULL) {
		printf(" Student id: %d, %s, %s", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa); // \n dupa fiecare nr grupa deoarece fgets pune LF (0x0a) in ultimul token de pe fiecare linie

		temp = temp->next;
	}

	ld = interschimbAdiacente(ld, 129);
	printf("\nTraversare lista dubla dupa interschimb adiacente:\n");
	temp = ld.prim;
	while (temp != NULL) {
		printf(" Student id: %d, %s, %s", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa); // \n dupa fiecare nr grupa deoarece fgets pune LF (0x0a) in ultimul token de pe fiecare linie

		temp = temp->next;
	}

	ld = interschimbNoduriOarecare(ld, 129, 99);
	printf("\nTraversare lista dubla dupa interschimb noduri oarecare:\n");
	temp = ld.prim;
	while (temp != NULL) {
		printf(" Student id: %d, %s, %s", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa); // \n dupa fiecare nr grupa deoarece fgets pune LF (0x0a) in ultimul token de pe fiecare linie

		temp = temp->next;
	}

	fclose(f);

}