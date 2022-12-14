#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>                  //указание прототипов
#include <stdlib.h>                 //библиотечных функций 
#include <windows.h>
#include <malloc.h>
#include <string.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};
struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data, int d){
	if (r == NULL){
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}
	if (d == 1 && data == r->data)
		return root;
	if (data > r->data)
		CreateTree(r, r->left, data, d);
	else
		CreateTree(r, r->right, data, d);

	return root;
}

void print_tree(struct Node* r, int l){

	if (r == NULL){
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++){
		printf(" ");
	}
	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}
int schet(struct Node* r, int l) {

	if (r == NULL) {
		return 0;
	}

	if (r->data == l) {
		return 1 + schet(r->right, l);
	}
	if (r->data > l) {
		return schet(r->right, l);
	}
	if (r->data < l) {
		return schet(r->left, l);
	}
}
int poisk(struct Node* r, int l){
	if (r == NULL){
		return 3;
	}
	if (r->data == l) {
		printf("\n%d нашли!\n", r->data);
		return 2;
	}
	if (r->data > l){
		return 10 * poisk(r->right, l) + 1;
		
	}
	if (r->data < l) {
		return 10 * poisk(r->left, l);
		
	}
}

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int D, start = 1, ddd = 1;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	printf("0 - разрешить/запретить повторения (запрещено)\n");
	while (start){
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1){
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		if (D == 0) {
			if (ddd == 1) {
				ddd = 0;
				printf("повторения разрещены\n");
			}
			else {
				ddd = 1;
				printf("повторения запрещены\n");
			}
		}
		else
			root = CreateTree(root, root, D, ddd);

	}

	print_tree(root, 0);

	printf("поиск:\n");
	scanf_s("%d", &D);
	printf("путь: %d\n", poisk(root, D));
	printf("количество: %d\n", schet(root, D));
	scanf_s("%d", &D);
	return 0;
}

