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
void cmp(char *ch) {
	StackType s;
	StackType n; // ��ȣ ��¿�
	init_stack(&s);
	init_stack(&n);
	char a = '0';
	int len = strlen(ch);
	char open_ch;
	for (int i = 0; i < len; i++) {
		switch (ch[i]) {
		case'(': case'{': case'[': {
			push(&n, ++a); // ��ȣ 1���� ���ÿ� �ֱ�
			push(&s, ch[i]); // ���� ��ȣ ���ÿ� �ֱ�
			printf("%c ", peek(&n)); // ��ȣ ���
			break;
		}

		case')': case'}': case']': {
			if (is_empty(&s)) {
				printf("\n���� ���� ��ȣ�� �����ϴ�.");
				return 0;
			} // ���� ��ȣ�� �������� ���� ������ȣ�� ������ ����
			else {
				open_ch = pop(&s);// ��ȣ�� ¦�� �´��� �Ǻ�
				if (open_ch == '(' && ch[i] != ')' ||
					open_ch == '{' && ch[i] != '}' ||
					open_ch == '[' && ch[i] != ']'){
					printf("\n��ȣ�� ¦�� ���� �ʽ��ϴ�");
					return 0;
				}
				else printf("%c ", pop(&n)); // �׿��ִ� ��ȣ ���
			}
			break;
		}
		}
	}
	if (!is_empty(&s)) printf("\n���� ��ȣ�� ���ҽ��ϴ�.");
		
}

int main(void) {
	char str[100];
	printf("���� �Է�:");
	scanf("%s", str);
	cmp(str);
	return 0;
}