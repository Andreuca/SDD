#include<stdio.h>

int suma_v1(int x, int y) {
	x += 1;
	int z = x + y;

	return z;
}

void suma_v2(int x, int y) {
	x += 1;
	int z = x + y;
}

void suma_v3(int x, int y, int z) {
	x += 1;
	z = x + y;
}

void suma_v4(int *x, int y, int *z) {
	*x += 1;
	*z = *x + y;
}

void main() {
	int a, b, c;

	a = 5;
	b = 7;

	c = suma_v1(a, b);
	printf("Suma_v1: \n a = %d \n b = %d \n c = %d \n", a, b, c);
	suma_v2(a, b);
	printf("Suma_v2: \n a = %d \n b = %d \n c = %d \n", a, b, c);
	suma_v3(a, b, c);
	printf("Suma_v3: \n a = %d \n b = %d \n c = %d \n", a, b, c);
	suma_v4(&a, b, &c);
	printf("Suma_v4: \n a = %d \n b = %d \n c = %d \n", a, b, c);


}