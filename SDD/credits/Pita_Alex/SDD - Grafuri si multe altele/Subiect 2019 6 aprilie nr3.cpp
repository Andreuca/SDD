#include <stdio.h>
#include <string.h>
#include <malloc.h>


struct Factura {
	char* serie;
	char* data;
	char* denumire;
	float valoare;
};

struct LSI {
	LSI* next;
	Factura factura;
};

Factura initFac(const char* serie, const char* data, const char* denumire, float valoare) {
	Factura factura;
	factura.serie = (char*)malloc(strlen(serie) + 1);
	strcpy_s(factura.serie, strlen(serie) + 1, serie);
	factura.data = (char*)malloc(strlen(data) + 1);
	strcpy_s(factura.data, strlen(data) + 1, data);
	factura.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(factura.denumire, strlen(denumire) + 1, denumire);
	factura.valoare = valoare;
	return factura;
}

void afisFac(Factura f) {
	printf("Factura cu seria %s din data %s apartine clientului %s si are valoarea de %4.1f.\n", f.serie, f.data, f.denumire, f.valoare);
}

LSI* inserareLSI(LSI* &cap, Factura f) {
	LSI* nou = (LSI*)malloc(sizeof(LSI));
	nou->factura = f;
	nou->next = cap;
	return nou;
}

void afisLSI(LSI* cap) {
	while (cap) {
		afisFac(cap->factura);
		cap = cap->next;
	}
}

int nrFac(LSI* cap, char* data) {
	int nr = 0;
	LSI* temp = cap;
	while (temp) {
		if (strcmp(temp->factura.data, data) == 0) {
			nr++;
		}
		temp = temp->next;
	}
	return nr;
}

LSI* returnList(LSI* &nou, LSI* cap, char* denumire) {
	if (cap) {
		LSI* nou2 = cap;
		while (nou2) {
			if (strcmp(nou2->factura.denumire, denumire) == 0) {
				nou = inserareLSI(nou, nou2->factura);
			}
			nou2 = nou2->next;
		}
		return nou;
	}
}

LSI* deleteLSI(LSI* cap) {
while(cap){
		LSI* temp = cap;
			cap = cap->next;
			free(temp->factura.data);
			free(temp->factura.denumire);
			free(temp->factura.serie);
			free(temp);
		}
	return cap;
}

LSI* deleteLSI2(LSI* cap) {
	while (cap) {
		LSI* temp = cap;
		cap = cap->next;
		free(temp);
	}
	return cap;
}



void main() {
	LSI* lsi = NULL;
	lsi = inserareLSI(lsi, initFac("DF1234", "09.04.2019", "Alexandru Dragomir", 508.1));
	lsi = inserareLSI(lsi, initFac("DE1234", "26.05.2019", "Cristea Iarina", 457.3));
	lsi = inserareLSI(lsi, initFac("EG1234", "09.04.2019", "Alexandru Dragomir", 782.5));
	lsi = inserareLSI(lsi, initFac("DH1234", "11.02.2019", "Alexandru Dragomir", 102.8));
	lsi = inserareLSI(lsi, initFac("AB1234", "09.04.2019", "Alexandra Vasile", 309.6));
	afisLSI(lsi);
	char buffer[20];
	printf("Dati data:"); scanf("%s", &buffer);
	char* data = (char*)malloc(strlen(buffer) + 1);
	strcpy(data, buffer);
	printf("Numarul facturilor emise la data %s este %d.\n", data,nrFac(lsi,data));
	
	LSI* lsi2 = NULL;
	lsi2 = returnList(lsi2, lsi, "Alexandru Dragomir");
	afisLSI(lsi2);
	deleteLSI(lsi);
	deleteLSI2(lsi2);

}