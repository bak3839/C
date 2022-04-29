#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX 10

typedef struct {
	short r;
	short c;
} element;


typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}
int is_full(StackType* s) { // ������ ���� ���ִ��� Ȯ��
	return (s->top == (MAX_STACK_SIZE - 1));
}

int is_empty(StackType* s) { // ������ ����ִ��� Ȯ��
	return (s->top == -1);
}

void push(StackType* s, element item) { // ���ÿ� ���� �ִ� �Լ�
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����");
		return;
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s) { // ���� ž ���� �� ���
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) { // ž�� �ִ� �� Ȯ��
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	else return s->data[(s->top)];
}
void print(char maze[MAX][MAX]) {
	printf("\n");
	for (int r = 0; r < MAX; r++) {
		for (int c = 0; c < MAX; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}
char maze[MAX][MAX] = {
	{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{ 'e', '0', '0', '1', '1', '0', '0', '0', '1', '1'},
	{ '1', '1', '0', '0', '0', '0', '1', '0', '0', '0'},
	{ '1', '1', '0', '1', '1', '1', '1', '1', '1', '0'},
	{ '1', '1', '0', '0', '0', '0', '0', '0', '0', 'x'},
	{ '1', '1', '0', '1', '1', '1', '1', '1', '1', '0'},
	{ '1', '1', '0', '0', '0', '1', '1', '1', '1', '0'},
	{ '1', '1', '1', '1', '0', '1', '1', '0', '0', '0'},
	{ '1', '1', '0', '0', '0', '0', '0', '0', '1', '0'},
	{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};
void location(StackType* s, int r, int c) {
	if (r < 0 || c < 0 || r >= MAX || c >= MAX) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element res;
		res.r = r;
		res.c = c;
		printf("                 PUSH [ %d , %d ]\n\n", r, c);
		push(s, res);
	}
}
element here = { 1,0 };
int main(viod) {
	StackType s;
	init_stack(&s);
	int r, c;

	while (1) {
		printf("( %d , %d )\n\n", here.r, here.c);
		printf("    |\n");
		printf("    V\n");
		while (maze[here.r][here.c] != 'x') {
			r = here.r;
			c = here.c;
			maze[r][c] = '.';
			// Ž�������� �� -> �Ʒ� -> �� -> ��

			// ���Լ����� �� -> �� -> �Ʒ� -> ��

			location(&s, r - 1, c); // ��
			location(&s, r + 1, c); // �Ʒ�
			location(&s, r, c - 1); // ��
			location(&s, r, c + 1); // ��

			if (is_empty(&s)) {
				printf("���� �����ϴ�.\n");
				return 0;
			}

			else {
				here = pop(&s);
				printf("( %d , %d )\n\n", here.r, here.c);
				printf("    |\n");
				printf("    V\n\n");
			}
		}
		printf("\n--------�ⱸ ����!!!--------\n\n");

		if (!is_empty(&s)) {
			printf("-----���ο�� Ž�� ����-----\n\n");
			here = pop(&s);
		}
		else break;
	}
	return 0;
}