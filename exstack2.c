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
int prec(char op) {
	switch (op) {
	case'(': return 0;
	case'&': case'|': return 1;
	case'>': case'<': case'=': return 2;
	case'+': case'-': return 3;
	case'*': case'/': return 4;
	case'^': return 5;
	}
	return -1;
}
void postfix(char *str) {
	char ch, top_op;
	int len = strlen(str);

	StackType s;
	init_stack(&s);

	for (int i = 0; i < len; i++) {
		ch = str[i];
		if (prec(ch) == -1) printf("%c", ch);
		else {
			if (is_empty(&s)) push(&s, ch); //������ ����ִٸ� �׳� Ǫ��

			else if (prec(peek(&s)) < prec(ch)) push(&s, ch); // ������ ������ ������ Ǫ��

			else { // ������ ������ ���ų� ������
				printf("%c", pop(&s));

				while (!is_empty(&s)) { // ���ÿ� ���� �ٸ� �����ڿ� ���� �����ڿ� ������ ��
					if (prec(peek(&s)) >= prec(ch)) printf("%c", pop(&s)); // ���ÿ� �ִ� �������� ������ ������ ��
					else break; // �ƴϸ� Ż��
				}

				push(&s, ch); // ���� �����ڸ� Ǫ��
			}
		}
	}
	while (!is_empty(&s)) { // ���ÿ� �����ִ� �����ڸ� ���
		printf("%c", pop(&s));
	}
}

int main(void) {
	char str[100];
	scanf("%s", str);
	postfix(str);
	return 0;
}