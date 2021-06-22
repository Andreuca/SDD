
#include<stdio.h>
#include<stdlib.h>

struct Student {
	int cod_matricol;
	char nume[30];
	float nota;
};
struct NodStudent {
	Student info;
	NodStudent* next;
};

struct HashStudent {
	int dimensiune;
	NodStudent** elemente;
};


Student citire_student() {
	Student s;
	printf("\nCod matricol: ");
	scanf_s("%d", &s.cod_matricol);
	getc(stdin);
	printf("\nNume: ");
	gets_s(s.nume, 30);
	printf("\nNota: ");
	scanf_s("%f", &s.nota);
	return s;
}

void afisare_student(Student s) {
	printf("\n%d %s %2.2f", s.cod_matricol, s.nume, s.nota);
}


int cod_hash(int cheie, HashStudent hs) {
	return cheie % hs.dimensiune;
}

HashStudent alocare_memorie() { 
	HashStudent hs;
	printf("\nIntroduceti dimensiunea hash: ");
	scanf_s("%d", &hs.dimensiune);
	hs.elemente = (NodStudent**)malloc(sizeof(NodStudent)*hs.dimensiune);
	for (int i = 0; i < hs.dimensiune; i++) {
		hs.elemente[i] = NULL;
	}
	return hs;
}

void dezalocare_lista(NodStudent* cap) {

	if (cap != NULL) {
		NodStudent* sters;
		while (cap != NULL) {
			sters = cap;
			cap = cap->next;
			free(sters);
		}
	}
}
void dezalocare_memorie(HashStudent hs) {

	if (hs.dimensiune > 0 && hs.elemente!=NULL) {
		for (int i = 0; i < hs.dimensiune; i++) {
			
			dezalocare_lista(hs.elemente[i]);
		}
		free(hs.elemente);
		hs.dimensiune = 0;
	}
}


int inserare(Student s, HashStudent &hs) {

	if (hs.dimensiune == 0 || hs.elemente == NULL || s.cod_matricol<0) {
		return -1;
	}
	int hash = cod_hash(s.cod_matricol, hs);

	if (hs.elemente[hash] == NULL) {
		hs.elemente[hash] = (NodStudent*)malloc(sizeof(NodStudent));
		hs.elemente[hash]->next = NULL;
		hs.elemente[hash]->info = s;
	}
	else {
		NodStudent* cursor = hs.elemente[hash];
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		
		NodStudent* nou = (NodStudent*)malloc(sizeof(NodStudent));
		nou->info = s;
		nou->next = NULL;
	
		cursor->next = nou;
	}
	return 1;
}

int stergere(int cod_matricol, HashStudent& hs) {

	if (hs.dimensiune == 0 || hs.elemente == NULL || cod_matricol<0) {
		return -1;
	}

	int hash = cod_hash(cod_matricol, hs);
	
	if (hs.elemente[hash] != NULL) {
	
		if (hs.elemente[hash]->info.cod_matricol == cod_matricol) {
			NodStudent* sters = hs.elemente[hash];
			hs.elemente[hash] = hs.elemente[hash]->next;
			sters->next = NULL;
			free(sters);
		} else {
			NodStudent* cursor = hs.elemente[hash];
			while (cursor->next != NULL && cursor->next->info.cod_matricol != cod_matricol) {
				cursor = cursor->next;
			}
			if (cursor->next != NULL && cursor->next->info.cod_matricol == cod_matricol) {
				NodStudent* sters = cursor->next;
				cursor->next = sters->next;
				sters->next = NULL;
				free(sters);
			}
			else {
				return -1;
			}
		}
	}
	else {
		return -1;
	}
	return 1;
}

void afisare_lista(NodStudent* cap) {
	if (cap != NULL) {
		NodStudent* cursor = cap;
		while (cursor != NULL) {
			afisare_student(cursor->info);
			cursor = cursor->next;
		}
	}
}

void afisare_hash(HashStudent hs) {
	printf("\nAfisare hash: ");
	if (hs.dimensiune == 0 || hs.elemente == NULL) {
		printf("\nNu exista element in hash");
	}
	else {
		for (int i = 0; i < hs.dimensiune; i++) {
			printf("\nElemente pozitia %d: ", i);
			afisare_lista(hs.elemente[i]);
		}
	}
}






void modificare_cheie(NodStudent* cap, char*nume) {
	if (cap != NULL) {
		NodStudent* cursor = cap;
		while (cursor != NULL && cursor->info.nume != nume) {
			free(cursor->info.nume);
			cursor->info.nume = (char*)malloc(sizeof(char) * 7);
			strcpy(cursor->info.nume, "numele");
			cursor = cursor->next;
		}
	}
}

void modificare_hash(HashStudent hs, char* nume) {
	printf("\nParcurgere: ");
	if (hs.dimensiune == 0 || hs.elemente == NULL) {
		printf("\nNu exista element in hash");
	}
	else {
		for (int i = 0; i < hs.dimensiune; i++) {
			modificare_cheie(hs.elemente[i], nume);
		}
	}
}


void adaugare_studenti_hash(HashStudent& hs) {
	int ok = 1;
	while (ok == 1) {
		Student s = citire_student();
		int rezultat = inserare(s, hs);
		printf("\nStudentul cu cod matricol %d a fost inserat cu %d", s.cod_matricol, rezultat);
		printf("\nContinuati? Da-1 Nu-0");
		scanf_s("%d", &ok);
	}
}

void stergere_student_cod_matricol(HashStudent& hs) {
	int cod;
	printf("\nCodul pe care doriti sa-l stergeti: ");
	scanf_s("%d", &cod);
	stergere(cod, hs);
}

void main() {
	printf("\n+++++++++++++++++++++++++alocare_memorie+++++++++++++++++++++++\n");
	HashStudent hs = alocare_memorie();
	afisare_hash(hs);
	printf("\n+++++++++++++++++++++adaugare_studenti_hash+++++++++++++++++++++++++++\n");
	adaugare_studenti_hash(hs);
	afisare_hash(hs);
	printf("\n+++++++++++++++++++++stergere_student_cod_matricol+++++++++++++++++++++++++++\n");
	stergere_student_cod_matricol(hs);
	afisare_hash(hs);
	dezalocare_memorie(hs);
}