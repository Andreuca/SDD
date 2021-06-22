#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Factura {
	int id;
	char* nume;
	float valoare;
};

struct NODE {
	Factura info;
	NODE *left;
	NODE* right;
};

Factura initFactura(int _id, const char* nume, float _val) {
	Factura f;
	f.id = _id;
	f.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(f.nume, nume);
	f.valoare = _val;
	return f;
}

void printFactura(Factura f) {
	printf("%d. Factura apartinand %s are valoarea %4.2f\n",f.id,f.nume,f.valoare);
}

NODE* initNode(Factura info) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->info = info;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

NODE* rotireLaStanga(NODE* root) {
	if (root) {
		NODE *aux = root->right;
		root->right = aux->left;
		aux->left = root;
		return aux; //e ca si cum as zice ca root = aux;

	}
	else {
		return nullptr;
	}
}


NODE* rotireLaDreapta(NODE* root) {
	if (root) {
		NODE *aux = root->left;
		if (root->left) {
			root->left = aux->right;
			aux->right = root;
			return aux; //e ca si cum as zice ca root = aux;
		}
	}
	else {
		return nullptr;
	}
}

int inaltimeArbore(NODE* root) {
	if (root) {
		int hs = inaltimeArbore(root->left);
		int hd = inaltimeArbore(root->right);
		return (hs > hd ? hs : hd) + 1;
	}
	else
		return 0;
}

int calculGradEchilibru(NODE *root) {
	if (root) {
		int hs = inaltimeArbore(root->left);
		int hd = inaltimeArbore(root->right);
		return (hs - hd);
	}
	else {
		return 0;
	}
}

NODE* insertTree(NODE* root, Factura f) {

if (root) {
		if (f.valoare < root->info.valoare) {
			root->left = insertTree(root->left, f);
			return root;
		}
		else {
			root->right = insertTree(root->right, f);
			return root;
		}
		//verificam daca pastreaza echilibrul
		int ge = calculGradEchilibru(root);
		if (ge == -2) {
			int ged = calculGradEchilibru(root->right);
			
			if (ged == -1) {
				root = rotireLaStanga(root);
			}
			else { root->left = rotireLaStanga(root->left);
			root = rotireLaDreapta(root);
			}
		}
			if (ge == 2) {
				int ges = calculGradEchilibru(root->left);
				if (ges == 1) {
					root = rotireLaDreapta(root);
				}
				else {
					root->right = rotireLaDreapta(root->right);
					root = rotireLaStanga(root);
				}

			}
	}
	else {
		return initNode(f);
	}
};







void printTree(NODE* root) {
	if (root) {
		printTree(root->left);
		printFactura(root->info);
		printTree(root->right);
	}
}

void main() {
	NODE* root = NULL;
	root = insertTree(root, initFactura(1, "Factura 1", 100));
	root = insertTree(root, initFactura(2, "Factura 2", 200));
	root = insertTree(root, initFactura(3, "Factura 3", 300));
	root = insertTree(root, initFactura(4, "Factura 4", 400));
	root = insertTree(root, initFactura(5, "Factura 5", 500));
	printTree(root);
	
}
