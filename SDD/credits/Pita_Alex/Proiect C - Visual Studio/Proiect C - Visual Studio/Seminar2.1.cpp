#include<stdio.h>
#include<malloc.h>

void main() {
	char c;
	char *pc, v[15];

	c = 65;
	printf(" %d - %c \n", c, c);

	pc = &c;
	*pc += 1;

	printf(" %d - %c \n", c, c);
	printf(" %d - %c \n", *pc, *pc);

	printf("Adrese variabile locale:\n");
	printf("Ard(c) = %X - Adr(pc) = %X - Ard(v) = %X \n", &c, &pc, &v);	// %X - pt a afisa adresa in Hexa
	printf("\nContinut variabila pointer:\n");
	printf("Adr(pc) = %X - Continut(pc) = %X - Adr(c) = %X\n", &pc, pc, &c);

	pc = (char*)malloc(c * sizeof(char));	// fortam alocarea unei zone de memorie heap (la runtime) - "fortarea" se face prin (char*) de dinaintea malloc-ului

	printf("Variabila pointer dupa alocare heap:\n");
	printf("Adr(pc) = %X - Continut(pc) = %X\n", &pc, pc);

	char* pv[15]; // vector de 15 locatii de tip pointer
	for (int i = 0; i < 15; i++)
		pv[i] = &v[i]; // sau se mai poate scrie ca: pv[i] = v + i;

	free(pc);	// dezalocare zona memorie heap
}