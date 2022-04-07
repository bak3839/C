#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void num_stack(char* str) {
	StackType s;
	init_stack(&s);
	int len = strlen(str);
	push(&s, str[0]);
	for (int i = 1; i < len; i++) {
		if (peek(&s) != str[i]) push(&s, str[i]);
	}
	char *result = malloc(sizeof(char) * (s.top + 2));
	int n = s.top + 1;
	result[n] = '\0';
	for (int i = n; i > 0; i--) result[i-1] = pop(&s);
	printf("%s", result);
	free(result);
}
int main(void) {
	char str[100];
	scanf("%s", str);
	num_stack(str);
	return 0;
}