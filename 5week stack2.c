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

element peek(StackType* s) { // ž�� �ִ� �� Ȯ��
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	else return s->data[(s->top)];
}
void run_length(char* str) {
	StackType s;
	init_stack(&s);
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
			if (is_empty(&s)) {
				push(&s, tolower(str[i]));
			}
			if (peek(&s) == tolower(str[i+1])) push(&s, tolower(str[i]));
			else {
				printf("%d%c ", (s.top) + 1, peek(&s));
				init_stack(&s);
			}
		}
	}
}
int main(void) {
	char str[100];
	printf("���ڿ� �Է�: ");
	gets(str);
	run_length(str);
	return 0;
}