#include<stdio.h>
#include<malloc.h>
#include<string>

void main() {
	// cosntruire (alocare si initializeaza) matrica zig-zag (fiecare linie are dim diferita);
	// se preteaza la siruri/vectori de string-uri

	int n = 0; // nr de string-uri/linii preluate din fisierul text
	char **pString, buffer[100]; // pointer la vector de string-uri
								 // buffer - vector continut temporar preluat din fisier
	FILE *f;

	f = fopen("Text.txt", "r");

	// determinare numar string-uri stocate in Text.txt
	while (fgets(buffer, sizeof(buffer), f)) {
		n += 1;
	}

	// alocare si populare matrice de string-uri
	pString = (char**)malloc(n * sizeof(char*));
	
	fseek(f, 0, SEEK_SET);
	int i = 0;
	while (fgets(buffer, sizeof(buffer), f)) { // fgets - preia si byte-ul 0x0A din fisier
		pString[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char)); // alocare linie i in mem heap
		strcpy(pString[i], buffer); // copiere continut din buffer in zona de heap aferenta liniei
		i += 1;
	}

	// afisare matrice zig-zag in consola de executie
	for (i = 0; i < n; i++) {
		printf("%s", pString[i]); // afisare string in consola
	}

	// dezalocare matrice (vector de string-uri)
	for (i = 0; i < n; i++)
		free(pString[i]);
	free(pString);

	// inchidere handler fisier
	fclose(f);
}