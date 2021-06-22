#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define MY_STRING "Anonymous"
#define ID_STUDENT 0
#define NR_GRUPA "0000"
#define DIM_VECTOR 10
#define NR_LINII 3
#define NR_COLOANE 4

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

void main() {
	Student s; // variabila de tip Student; alocata la compilare in Frame-ul de seg de stack aferent lui main
	Student vStud[20]; // variabila masiv de tip Student; 20 locatii alocate la compilare, fiecare locatie este Student
	Student * pStud; // vector de studenti alocat la run-time
	Student ** mStud; // matrice de studenti alocata la run-time
	Student* * vpStud; //vector de pointeri la studenti

	printf("Dimensiunea structura student in nr de bytes: %d\n", sizeof(Student));

	s.id = ID_STUDENT;
	s.nume = (char*)malloc(sizeof(char) * (strlen(MY_STRING) + 1)); // alocare spatiu in heap pentru nume student
	strcpy(s.nume, MY_STRING); // copiere string default pentru nume student
	strcpy(s.nrGrupa, NR_GRUPA); // copiere valoare default nr grupa

	for (int i = 0; i < DIM_VECTOR; i++) {
		// vStud[i] = s; // copiere byte cu byte al lui s in vStdu[i]; !!! campul nume are acelasi continut (aceeasi adresa de heap)
		vStud[i].id = s.id;
		
		vStud[i].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
		strcpy(vStud[i].nume, s.nume);
		
		strcpy(vStud[i].nrGrupa, s.nrGrupa);
	}

	pStud = (Student*)malloc(sizeof(Student) * DIM_VECTOR);
	for (int i = 0; i < DIM_VECTOR; i++) {
		// pStud[i] = s; // copiere byte cu byte al lui s in vStdu[i]; !!! campul nume are acelasi continut (aceeasi adresa de heap)
		pStud[i].id = s.id;

		pStud[i].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
		strcpy(pStud[i].nume, s.nume);

		strcpy(pStud[i].nrGrupa, s.nrGrupa);
	}

	// mStud construit ca matrice de Studenti
	mStud = (Student**)malloc(sizeof(Student*) * NR_LINII); // structura intermediara; vector de pointeri la linii
	for (int i = 0; i < NR_LINII; i++) {
		mStud[i] = (Student*)malloc(sizeof(Student) * NR_COLOANE); // alocare heap pentru linia i
	}

	for(int i=0;i<NR_LINII;i++)
		for (int j = 0; j < NR_COLOANE; j++) {
			mStud[i][j].id = s.id;
			
			mStud[i][j].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
			strcpy(mStud[i][j].nume, s.nume);

			strcpy(mStud[i][j].nrGrupa, s.nrGrupa);
		}

	vpStud = (Student**)malloc(sizeof(Student*) * DIM_VECTOR);
	for (int i = 0; i < DIM_VECTOR; i++) {
		vpStud[i] = (Student*)malloc(sizeof(Student) * 1); // alocarea unui singur student
	}

	for (int i = 0; i < DIM_VECTOR; i++) {
		// *(vpStud[i]) = s;
		vpStud[i]->id = s.id;

		vpStud[i]->nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
		strcpy(vpStud[i]->nume, s.nume);

		strcpy(vpStud[i]->nrGrupa, s.nrGrupa);
	}

	// Dezalocari structuri
	free(s.nume);

	// vector de studenti alocat in stack segment
	for (int i = 0; i < DIM_VECTOR; i++) {
		free(vStud[i].nume);
	}

	// vector de studenti alocat in heap segment
	for (int i = 0; i < DIM_VECTOR; i++) {
		free(pStud[i].nume);
	}

	// matrice de studenti alocata in heap
	for (int i = 0; i < NR_LINII; i++)
		for (int j = 0; j < NR_COLOANE; j++) {
			free(mStud[i][j].nume); // dezalocare nume studenti [i][j]
		}

	for (int i = 0; i < NR_LINII; i++) {
		free(mStud[i]); // deazalocare linie i
	}

	free(mStud); // dezalocare structura intermediara (vector pointeri la linii)

	// vector de pointeri la studenti
	for (int i = 0; i < DIM_VECTOR; i++)
		free(vpStud[i]->nume); // dezalocare nume student i
	free(vpStud); // dezalocare vector de adrese de studenti
}