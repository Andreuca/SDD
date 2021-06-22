#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Evaluation {
	int evaluationId;
	int noCredits;
	char* examName;
	int studentId;
	double grade;
};
struct nod {
	Evaluation info;
	nod* next;

};
struct BinaryTree {
	Evaluation info;
	BinaryTree* left;
	BinaryTree* right;
};


/////////////////////////////////////
void display_evaluation(Evaluation eval) {
	printf("\nEvaluationId: %d; noCredits: %d; examName: %s ;evaluationId: %d ; grade: %f;", eval.evaluationId, eval.noCredits, eval.examName, eval.studentId, eval.grade);

}
void display_evaluations(Evaluation* evals, int nr) {
	for (int i = 0; i < nr; i++) {
		display_evaluation(evals[i]);
	}
}


BinaryTree* create_node(Evaluation eval, BinaryTree* left, BinaryTree* right) {
	BinaryTree* nou = (BinaryTree*)malloc(sizeof(BinaryTree));
	nou->info= eval;
	

	nou->right = right;
	nou->left = left;
	return nou;
}

BinaryTree* insert_node(Evaluation eval, BinaryTree* root) {
	if (root) {
		if (root->info.evaluationId > eval.evaluationId) {
			root->left = insert_node(eval, root->left);
		}
		else {
			root->right = insert_node(eval, root->right);
		}
		return root;
	}
	else {
		return create_node(eval, NULL, NULL);
	}
}
void copy_tree(nod* head,  BinaryTree*& root) {
	nod* cursor;
	cursor = head;

	do   {
	
		root = insert_node(cursor->info, root);
		cursor = cursor->next;
	} while (cursor != head);
}

void inorder_traversal(BinaryTree* root) {
	if (root) {
		
		inorder_traversal(root->left);
		display_evaluation(root->info);
		inorder_traversal(root->right);
	}
}

void free_btree(BinaryTree*& root) {
	if (root) {
		free_btree(root->right);
		free_btree(root->left);
		free(root);
		root = NULL;
	}
}
/// 
/// //////////////////////////////

nod* create_list(Evaluation* ev, int& nr) {
	nod* head = NULL;
	if (nr > 0) {
		head = (nod*)malloc(sizeof(nod));
		head->next = NULL;
		head->info = ev[0];
		nod* cursor, * nou;
		cursor = head;
		for (int i = 1; i < nr; i++) {

			nou = (nod*)malloc(sizeof(nod));
			nou->next = NULL;
			nou->info = ev[i];
			cursor->next = nou;
			cursor = nou;

		}

		cursor->next = head;
	}
	return head;
}

void list_display(nod* head) {
	printf("\nShow List\n");
	nod* cursor;
	cursor = head;
	do {
		printf("\nEvaluationId: %d; noCredits: %d; examName: %s ;evaluationId: %d ; grade: %f;", cursor->info.evaluationId, cursor->info.noCredits, cursor->info.examName, cursor->info.studentId, cursor->info.grade);
		cursor = cursor->next;
	} while (cursor != head);
}



/// /////////////////


void delete_elements(nod*& head, int studentId) {
	nod* cursor;
	cursor = head;
	if (cursor->info.studentId == studentId)
	{
		cursor = head->next;
		free(head);
	}
	
		while ( cursor->next != head)
		{
			if (cursor->next->info.studentId == studentId) {
				nod* deleted = cursor->next;
				cursor->next = deleted->next;
				free(deleted);
			}
			cursor = cursor->next;
		}
}

/// ///////////////////////////

void dealocationn(nod* head)
{
	nod* temp = head;
	nod* temp2 = temp->next;
	free(temp);
	temp = temp2;
	while (temp != head)
	{
		nod* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}
void main() {
	FILE* file = fopen("Rosianu_Andreea.txt", "r");
	char buffer[128];
	char* token;
	char splitter[] = { "," };

	int nr = 0, i = 0;
	fscanf(file, "%d", &nr);
	fgetc(file);

	Evaluation* evaluations = (Evaluation*)malloc(sizeof(Evaluation) * nr);

	while (fgets(buffer, 128, file)) {

		Evaluation a;
		token = strtok(buffer, splitter);
		a.evaluationId = atoi(token);

		token = strtok(NULL, splitter);
		a.noCredits = atoi(token);

		token = strtok(NULL, splitter);
		a.examName = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(a.examName, token);

		token = strtok(NULL, splitter);
		a.studentId = atoi(token);

		token = strtok(NULL, splitter);
		a.grade = atoi(token);

		evaluations[i++] = a;
	}
	nod* head = NULL;
	printf("\n------------------1---------------\n");
	head = create_list(evaluations, nr);
	list_display(head);
	printf("\n------------------4 ------------------\n");
	BinaryTree* root = NULL;
	copy_tree(head, root);
	inorder_traversal(root);
	printf("\n------------------ 3 ------------------\n");
	delete_elements(head,32);
	list_display(head);

	//
	dealocationn(head);
	free_btree(root);

	
	
}
