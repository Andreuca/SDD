#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define DIM 100

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct Nod {
	Student stud; // date propriu-zise
	Nod* next; // date de legatura (relatie de ordine pe elemente de tip Nod)
};

Nod* inserareSfarsitLista(Nod* p, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod)); // alocare nod nou
	// nou->stud = s; // copiere inclusiv nrGrupa !!!
	nou->stud.id = s.id;
	nou->stud.nume = s.nume; // asumare s.nume va fi copiat peste nou->nume
	strcpy(nou->stud.nrGrupa, s.nrGrupa);
	nou->next = NULL;

	if (p == NULL) // lista nu contine nici un nod/element
		return nou;
	else {
		// parsare lista pana pe ultimul element
		Nod* temp = p;
		while (temp->next != NULL)
			temp = temp->next;
		// legare ultimul nod din lista la nodul nou
		temp->next = nou;
	}

	return p;
}

// stergere nod din lista
Nod* stergereNodInceput(Nod* lst) {
	Nod * temp = lst;

	if (lst) {
		lst = lst->next; // actualizare nod de inceput lista

		free(temp->stud.nume); // dezalocare mem heap pt nume student
		free(temp);			// dezalocare mem heap pt nod din lista
	}

	return lst;
}

// Stergere nod din lista (pe baza nume student)
// se vor sterge toti studentii cu acelasi nume
Nod* stergereNodNumeStudent(Nod* lst, char* numeStud) {
	if (lst != NULL) {
		// !!! TEMA  - actualizare stergere la inceput cu parsarea listei in intregime pt situatia in care exista
		// mai multi studenti cu acelasi nume in lista
		char* nume = new char[strlen(numeStud) + 1];
		strcpy(nume, numeStud);

		Nod* lstTmp = NULL;

		while (lst) {
			Nod* q = lst;
			if (strcmp(q->stud.nume, nume) == 0) {
				// q este nodul de sters, tmp este predecesorul lui q
				lst = q->next; // izolare q fata de lista
				delete[] (q->stud.nume);
				
			}
			else {
				lstTmp = inserareSfarsitLista(lstTmp, q->stud);
				lst = lst->next;		
			}
			delete[] q;
		}
		delete[] nume;

		return lstTmp;
	}

	return lst;
}

// implementare functii hash (nume student: cheie de cautare)
int functieHash(char* str, int size) { // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i < strlen(str); i++)
		temp += str[i];

	poz = temp % size;

	printf("%d %d  ", temp, poz);

	return poz;
}

// inserare student in tabela de dispersie(chaining)
void inserareHTable(Nod** hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = functieHash(s.nume, sizeHT);

	hTab[k] = inserareSfarsitLista(hTab[k], s);
}

// parsare tabela de dispersie(in intregime, secvential)
void parseHTable(Nod** hTab, int size) {
	for (int i = 0; i < size; i++) {
		if (hTab[i]) { // lista i contine cel putin un student
			Nod* tmp = hTab[i];
			printf("  Lista no. %d:\n", i);
			while (tmp) {
				printf("    %d  %s\n", tmp->stud.id, tmp->stud.nume);
				tmp = tmp->next;
			}
		}
	}
}

// cautare student in tabela hash dupa cheia de cautare (nume student)
// functia intoarce student(gasit->nume nu este NULL; sau neidentificat in tabela hash->nume este NULL)
Student cautaHTabel(Nod** hTab, int size, char* numeStud) {
	int k; // pozitie probabila pentru string-ul nume
	k = functieHash(numeStud, size);

	Nod* tmp = hTab[k];
	while (tmp) {

		if (!strcmp(tmp->stud.nume, numeStud))
			return tmp->stud;

		tmp = tmp->next;
	}

	Student retStud;
	retStud.nume = NULL;
	return retStud;
}

// Stergerea unui student din tabela hash pe baza numelui si sa-l eliminam(Dupa schema cautaHTable)
// functia intoarce 1 (studentul exista) pentru succes, 0 pentru esec (studentul nu a fost identificat)
char stergereHTable(Nod** hTab, int size, char* numeStud) {
	int k; // pozitie probabila pentru string-ul nume
	k = functieHash(numeStud, size);

	Nod* tmp = hTab[k];
	while (tmp) {
		if (!strcmp(tmp->stud.nume, numeStud)) {
			hTab[k] = stergereNodNumeStudent(hTab[k], tmp->stud.nume);
			return 1;
		}

		tmp = tmp->next;
	}

	return 0;
}

void main() {
	Nod* *HTable;
	Student stud;
	
	// alocare spatiu tabela de dispersie
	HTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	// initializare elemente tabela de dispersie
	for (int i = 0; i < DIM; i++) {
		HTable[i] = NULL; // HTable[i] => elementul i in tabela hash
	}

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		// alocare (nume) si initializare student
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(stud.nrGrupa, token);

		token = strtok(NULL, sep_list); // verificare existenta token dupa medie in linia curenta file_buf
		if (token)
			printf("\nEroare preluare token!");
		
		// inserare Student in Tabela Hash
		inserareHTable(HTable, stud, DIM);
		printf("Student %s inserat \n", stud.nume);

		stud.nume = NULL; // evitare partajare zona heap pentru nume student
	}

	// afisare in consola continut tabela dispersie
	printf("\nTabela de dispersie:\n");
	parseHTable(HTable, DIM);

	stud = cautaHTabel(HTable, DIM, (char*)"Marinescu George");
	if (stud.nume != NULL) {
		// studentul a fost identificat
		printf("\n\nStudent identificat: %d %s %s\n", stud.id, stud.nume, stud.nrGrupa);
	}
	else {
		printf("\n\nStudentul nu exista in tabela hash.\n");
	}

	if (stergereHTable(HTable, DIM, (char*)"Marinescu George")) {
		printf("\n\nStudentul a fost sters cu succes!");
	}
	else
		printf("\n\nStudentul nu a fost sters!");

	// afisare in consola continut tabela dispersie
	printf("\n\nTabela de dispersie:\n");
	parseHTable(HTable, DIM);

	fclose(f);
}