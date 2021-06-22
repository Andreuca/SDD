#include<stdio.h>

int nrCifrePrime(long n) {
	if (n / 10 < 1 && n%10 == 0) {
		return 0;
	}
	else if (n%10 == 2 || n % 10 == 3 || n % 10 == 5 || n % 10 ==7) {
		return nrCifrePrime(n / 10) + 1;
	}
	else {
		return nrCifrePrime(n / 10);
	}
}

void main() {
	long n;
	printf("Introduceti numarul: ");
	scanf("%ld", &n);
	int nrCifre = nrCifrePrime(n);
	printf("Numarul de cifre prime este: %d.", nrCifre);
}