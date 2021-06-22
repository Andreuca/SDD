#include <stdio.h>
#include<string.h>
#include <malloc.h>

struct Fisier {
	char* denumire_fisier;
	char* extensie_fisier;
	unsigned int dim;
};

struct HashTable {
	Fisier **f;
	int dim;
};

Fisier* initFisier(const char* den, const char* ext, int dim) {
	Fisier*f = (Fisier*)malloc(sizeof(Fisier));
	f->denumire_fisier = (char*)malloc(strlen(den) + 1);
	strcpy_s(f->denumire_fisier, strlen(den) + 1, den);
	f->extensie_fisier = (char*)malloc(strlen(ext) + 1);
	strcpy_s(f->extensie_fisier, strlen(ext) + 1, ext);
	f->dim = dim;
	return f;
}

void afisFisier(Fisier f) {
	printf("%s.%s are dimensiunea %d bytes.\n", f.denumire_fisier, f.extensie_fisier, f.dim);

}

int hashCode(Fisier f,HashTable ht) {
	return (unsigned int)f.denumire_fisier % ht.dim;
}

HashTable init(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.f = (Fisier**)malloc(sizeof(Fisier*)*ht.dim);
	for (int i = 0; i < ht.dim; i++) {
		ht.f[i] = NULL;
	}
	return ht;
}

int inserareInHT(HashTable &ht, Fisier* f) {
	if (ht.dim>0) {
		int index = hashCode(*f, ht);
		if (ht.f[index]) {
			int pozitie = (index + 1)%ht.dim;
			while (ht.f[pozitie] != NULL && index != pozitie) {
				pozitie=(pozitie+1)%ht.dim;
			}if (index == pozitie)
				return -1; 
				
			else {
				ht.f[pozitie] = f;
				return pozitie;
			}
		}
		else {
			ht.f[index] = f;
			return index;
		}
	}
	else return -2;
}

Fisier cautaInHT(HashTable ht, Fisier *f) {
	
	if (ht.dim > 0) {
		int index = hashCode(*f, ht);
		if (strcmp(ht.f[index]->denumire_fisier, f->denumire_fisier) == 0) { //deepcopy trebuie facut bla bla bla
			Fisier rez = *ht.f[index];
			return rez;
		}
		else {
			int pozitie = index;
			do {
				pozitie = (pozitie + 1) % ht.dim;
				if ( strcmp(ht.f[pozitie]->denumire_fisier,f->denumire_fisier)==0)
					break;
			} while (index != pozitie );
			if (index==pozitie) {
				Fisier rez = *initFisier("0", "ksda", 0);
				return rez;
			}
			else {
				Fisier* rez = ht.f[pozitie];
				return *rez;
			}
		}
	}
	else {
		Fisier rez=*initFisier("0", "asdadas", 0);
		return rez;
	}
}

void afisareTabela(HashTable h) {
	for (int i = 0; i < h.dim; i++)
	{
		if (h.f[i] != NULL) {
			afisFisier(*h.f[i]);
		}
	}
}
void schimbareExtensie(HashTable &ht, Fisier *f, const char *ext) {
	Fisier fis = cautaInHT(ht, f);
	if (strcmp(fis.denumire_fisier, "0") == 0) printf("\nNu exista ma fisierul\n");
	else {
		free(fis.extensie_fisier);
		fis.extensie_fisier = (char*)malloc(strlen(ext) + 1);
		strcpy_s(fis.extensie_fisier, strlen(ext) + 1, ext);
	}
}

void main() {
	HashTable ht;
	ht = init(5);
	inserareInHT(ht, initFisier("Seminar", "txt", 128));
	inserareInHT(ht, initFisier("Java", "class", 256));
	inserareInHT(ht, initFisier("FirstApp", "js", 512));
	inserareInHT(ht, initFisier("App", "cs", 1024));
	inserareInHT(ht, initFisier("Source", "cpp", 2049));
	afisareTabela(ht);
	Fisier* f = initFisier("Seminar", ".asda", 18);
	*f = cautaInHT(ht, f);
	afisFisier(*f);
	printf("-----------------------------------------------------------------\n");
	schimbareExtensie(ht, f, "bin");
	afisareTabela(ht);


}
