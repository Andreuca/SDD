#include<stdio.h>
#include<malloc.h>

void main() {
	
	int mat[10][20], **pMat; //

	pMat = (int**)malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; i++)
		pMat[i] = (int*)malloc(sizeof(int) * 20);

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
			pMat[i][j] = i * 10 + j;

	// dezalocare matrice pMat - invers alocarii
	for (int i = 0; i < 10; i++)
		free(pMat[i]);
	free(pMat);

}