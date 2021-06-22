/* 
Arbore binar asezare:
Daca e mai mic se duce in stanga - Daca e mai mic si decat fiul - atunci tot in stanga, altfel in dreapta fiului
Daca e mai mare se duce in dreapta - Daca e mai mare si decat fiul - atunci tot dreapta, altfel in stanga fiului
Poza tel - 14 mai
*/

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodABC{
	Student s;
	NodABC* st, *dr;
};

NodABC* inserare(NodABC *r, Student st, int &er)
{
	if (r == NULL) {
		NodABC *nou = new NodABC;
		nou->dr = NULL;
		nou->st = NULL;
		//nou->s = st;
		nou->s.id = st.id;
		nou->s.nume = st.nume;
		strcpy(nou->s.nrGrupa, st.nrGrupa);

		r = nou;
	}
	else if (r->s.id == st.id) er = 1;
	else if (r->s.id > st.id)
		r->st = inserare(r->st, st, er);
	else
		r->dr = inserare(r->dr, st, er);

	return r;
}

void traversareInordine(NodABC *r) {
	if (r) {
		traversareInordine(r->st);
		printf("%d %s\n", r->s.id, r->s.nume);
		traversareInordine(r->dr);
	}
}

void nrFrunze(NodABC *r, int &nr) {
	if (r) {
		nrFrunze(r->st, nr);
		
		// prelucrare/vizitare nod curent
		if (r->st == NULL && r->dr == NULL)
			nr += 1;

		nrFrunze(r->dr, nr);
	}
}

// !!Tema - salvareIDFrunze !!
void salvareIDFrunze(NodABC *r, int* vFrunze, int &offset) {
	if (r) {
		salvareIDFrunze(r->st, vFrunze, offset);

		if (r->st == NULL && r->dr == NULL) {
			vFrunze[offset] = r->s.id;
			offset++;
		}

		salvareIDFrunze(r->dr, vFrunze, offset);
	}
}

// TEMA
// determinare nr noduri ABC
int nrNoduri(NodABC* r) {
	if (r == NULL)
		return 0;
	else
		return nrNoduri(r->st) + 1 + nrNoduri(r->dr);
}

// determinare inaltime ABC
int inaltimeArbore(NodABC* r) {
	if (r == NULL)
		return 0;
	else {
		int stanga = inaltimeArbore(r->st);
		int dreapta = inaltimeArbore(r->dr);

		if (stanga > dreapta)
			return stanga + 1;
		else
			return dreapta + 1;
	}
}

// determinare nr noduri de pe un nivel specificat in ABC
int nrNoduriPeNivel(NodABC* r, int curent, int niv) {
	if (r == NULL)
		return 0;
	else if (curent == niv)
		return 1;
	else
		return nrNoduriPeNivel(r->st, curent + 1, niv) + nrNoduriPeNivel(r->dr, curent + 1, niv);
}

// salvare noduri (cheie id student) intr-un vector de pe un nivel specificat in ABC
void vectorNoduriNivel(NodABC* r, int curent, int niv, int* vNoduriNivel, int& offset) {
	if (r) {
		if (curent == niv) {
			vNoduriNivel[offset] = r->s.id;
			offset++;
		}
		
		curent++;
		vectorNoduriNivel(r->st, curent, niv, vNoduriNivel, offset);
		vectorNoduriNivel(r->dr, curent, niv, vNoduriNivel, offset);
	}
}

// traversare preordine ABC
void traversarePreordine(NodABC *r) {
	if (r) {
		printf("%d %s\n", r->s.id, r->s.nume);
		traversarePreordine(r->st);
		traversarePreordine(r->dr);
	}
}

// traversare postordine ABC
void traversarePostordine(NodABC* r) {
	if (r) {
		traversarePostordine(r->st);
		traversarePostordine(r->dr);
		printf("%d %s\n", r->s.id, r->s.nume);
	}
}

// traversare pe niveluri ABC
void afisareNoduriPeNivel(NodABC* r, int niv) {
	if (r) {
		if (niv == 0) {
			printf("%d %s\n", r->s.id, r->s.nume);
		}
		else if (niv > 0) {
			afisareNoduriPeNivel(r->st, niv - 1);
			afisareNoduriPeNivel(r->dr, niv - 1);
		}
	}
}

void traversarePeNiveluri(NodABC* r) {
	for (int i = 0; i < inaltimeArbore(r); i++) {
		afisareNoduriPeNivel(r, i);
	}
}

// stergere nod din ABC
NodABC* minVal(NodABC* r) {
	NodABC* temp = r;

	while (temp->st) {
		temp = temp->st;
	}

	return temp;
}

NodABC* stergereNod(NodABC* r, int idStud) {
	if (r == NULL)
		return r;
	else if (idStud < r->s.id)
		r->st = stergereNod(r->st, idStud);
	else if (idStud > r->s.id)
		r->dr = stergereNod(r->dr, idStud);
	else {
		if (r->st == NULL) {
			NodABC* temp = r->dr;
			free(r->s.nume);
			free(r);

			return temp;
		}
		else if (r->dr == NULL) {
			NodABC* temp = r->st;
			free(r->s.nume);
			free(r);

			return temp;
		}

		NodABC* temp = minVal(r->dr);
		r->s.id = temp->s.id;
		r->s.nume = (char*)malloc(sizeof(char) * (strlen(temp->s.nume) + 1));
		strcpy(r->s.nume, temp->s.nume);
		strcpy(r->s.nrGrupa, temp->s.nrGrupa);

		r->dr = stergereNod(r->dr, temp->s.id);
	}

	return r;
}

NodABC* dezalocare(NodABC* r) {
	if (r == NULL)
		return r;
	else {
		dezalocare(r->st);
		dezalocare(r->dr);
		free(r->s.nume);
		free(r);
	}
}

void main() {
	Student stud;
	NodABC* root = NULL;

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		int err = 0;
		
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(stud.nrGrupa, token);

		token = strtok(NULL, sep_list); // verificare existenta token dupa medie in linia curenta file_buf
		if (token)
			printf("\nEroare preluare token!");
		// apel functie inserare nod in lista simpla
		
		root = inserare(root, stud, err);

		if (err) {
			printf("\nStudentul cu id %d exista in arbore.\n", stud.id);
			free(stud.nume);
		}
		else {
			printf("\nStudentul cu id %d a fost inserat.", stud.id);
		}

		stud.nume = NULL;
	}

	// validare structura arbore binar de cautare
	printf("\nArbore binar de cautare dupa creare(traversare inordine):\n");
	traversareInordine(root);

	int nrFrunzeABC = 0;
	nrFrunze(root, nrFrunzeABC);
	printf("\nArborele are nr de frunze = %d\n", nrFrunzeABC);

	int* vIDFrunze = new int[nrFrunzeABC];
	int i = 0; // offset element 1 in vector
	salvareIDFrunze(root, vIDFrunze, i);

	printf("\nId-ul frunzelor:");
	for (int j = 0; j < nrFrunzeABC; j++) {
		printf("\nv[%d] = %d", j, vIDFrunze[j]);
	}

	printf("\n\nNumarul de noduri este: %d.", nrNoduri(root));

	printf("\n\nNumarul de noduri de pe nivelul 1 este: %d.\n\n", nrNoduriPeNivel(root, 0, 1));

	int* vFrunzeNivel = new int[nrNoduri(root)];

	i = 0;
	vectorNoduriNivel(root, 0, 1, vFrunzeNivel, i);
	printf("ID-urile studentilor de pe nivelul 1 al arborelui sunt:\n");
	for (int j = 0; j < i; j++) {
		printf("v[%d] = %d\n", j, vFrunzeNivel[j]);
	}

	printf("\nArbore binar de cautare (traversare preordine):\n");
	traversarePreordine(root);

	printf("\nArbore binar de cautare (traversare postordine):\n");
	traversarePostordine(root);

	printf("\nArbore binar de cautare (traversare pe niveluri):\n");
	traversarePeNiveluri(root);

	printf("\nArbore binar de cautare dupa stergere student cu ID 83 (traversare inordine):\n");
	stergereNod(root, 83);
	traversareInordine(root);

	root = dezalocare(root);
	printf("\nArbore binar de cautare (traversare pe niveluri) dupa dezalocare:\n");
	traversarePeNiveluri(root);

	fclose(f);
}