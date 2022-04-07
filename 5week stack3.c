#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

typedef char element;
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
int cmp(char* str) {
	StackType s;
	init_stack(&s);
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
			str[i] = tolower(str[i]);
			push(&s, str[i]);
		}
	}
	printf("----------------\n");
	for (int i = 0; i < len / 2; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			if (pop(&s) == str[i]) continue;
			else return 0;
		}
	}
	return 1;
}

int main(void) {
	char str[100];
	printf("���ڿ� �Է�: ");
	gets(str);
	if (cmp(str) == 1) printf("ȸ���Դϴ�.");
	else printf("ȸ���� �ƴմϴ�.");
	return 0;
}