#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef int element;
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
	switch (op) { // �������� ���������� �Ǻ�
	case'&': case'|': case'>': 
	case'<': case'=': case'+':
	case'-': case'*': case'/': case'^': return 0;
	}
	return -1;
}
int calstr(char* str) {
	StackType s;
	init_stack(&s);
	int ch1, ch2, value;
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if (prec(str[i]) == -1) { // prec���� -1�� ��ȯ�Ǹ� ����
			value = str[i] - '0'; // ���������� �ٲ㼭 ����
			printf("< %d > --- push\n\n", value);
			push(&s, value); // ���ÿ� ����
		}
		else { // �������� ��� ���ÿ� �ִ� �� 2���� ������ ����
			ch1 = pop(&s); 
			printf("< %d > --- pop\n\n", ch1);
			ch2 = pop(&s); 
			printf("< %d > --- pop\n\n", ch2);

			switch (str[i]) {
			case'+': {
				push(&s, ch2 + ch1);
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, ch2 + ch1);
				break;
			}
			case'-': {
				push(&s, ch2 - ch1);
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, ch2 - ch1);
				break;
			}
			case'*': {
				push(&s, ch2 * ch1); 
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, ch2 * ch1);
				break;
			}
			case'/': {
				push(&s, ch2 / ch1);
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, ch2 / ch1);
				break;
			}
			case'^': {
				int sum = 0;
				for (int i = 0; i < ch1; i++) sum *= ch2;
				push(&s, sum); 
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, sum);
				break;
			}
			case'>': {
				if (ch2 > ch1) push(&s, 1);
				else push(&s, 0);
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, peek(&s));
				break;
			}
			case'<': {
				if (ch2 < ch1) push(&s, 1);
				else push(&s, 0);
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, peek(&s));
				break;
			}
			case'=': {
				if (ch2 == ch1) push(&s, 1);
				else push(&s, 0);
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, peek(&s));
				break;
			}
			case'&': {
				if (ch2 && ch1) push(&s, 1);
				else push(&s, 0);
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, peek(&s));
				break;
			}
			case'|': {
				if (ch2 || ch1) push(&s, 1);
				else push(&s, 0);
				printf("< %d %c %d > result: %d  --- push\n\n", ch2, str[i], ch1, peek(&s));
				break;
			}
			}
		}

	}
	printf("<----------------------------------->\n\n");
	return pop(&s);
}//34+2-222^*>73-2/52*&
int main(void) {
	char str[100];
	printf("���� ����� �Է�: ");
	scanf("%s", str);
	printf(" ----���� ���: %d----", calstr(str));
	return 0;
}