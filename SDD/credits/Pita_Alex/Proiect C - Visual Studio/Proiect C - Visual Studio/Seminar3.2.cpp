#include<stdio.h>
#include<malloc.h>

int* alocareVector(int n) {
	int *z = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		z[i] = 0;
	}

	return z;
}

void main() {
	int m, v[20], *pv;
	m = 13;

	for (int i = 0; i < 20; i++) {
		v[i] = i * 10 + i;
	}

	pv = alocareVector(m);
	for (int i = 0; i < m; i++) {
		pv[i] = v[i] + 1;
	}
	
	for (int i = 0; i < m; i++) {
		printf("pv[%d] = %d\n", i, pv[i]);
	}

	int mat[10][20], **pMat;

	pMat = (int**)malloc(sizeof(int*) * 10); // alocare vecotr de pointer la linii - structura intermediara
	for (int i = 0; i < 10; i++) {
		pMat[i] = (int*)malloc(sizeof(int) * 20);
	}

	// TEMA : Initializare cu valori a matricei pMat; dezalocarea matricei pMat; construire (alocare si initializare) matrice zig-zag (fiecare linie are dimensiune diferita)
	// se preteaza la siruri/vectori de string-uri

	for(int i=0;i<10;i++)
		for (int j = 0; j < 20; j++) {
			pMat[i][j] = (i + j) / 2 + (i * j);
		}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++)
			printf("%d ", pMat[i][j]);
		printf("\n");
	}
		
	for (int i = 0; i < 10; i++)
		free(pMat[i]);

	free(pMat);

	free(pv);
}