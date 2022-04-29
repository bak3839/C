#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int num[MAX_STACK_SIZE];
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

void push_num(StackType* s, int item) { // ������
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����");
		return;
	}
	else s->num[++(s->top)] = item;
}

element pop(StackType* s) { // ���� ž ���� �� ���
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	else return s->data[(s->top)--];
}

int pop_num(StackType* s) { // ������
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	else return s->num[(s->top)--];
}

element peek(StackType* s) { // ž�� �ִ� �� Ȯ��
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	else return s->data[(s->top)];
}

int peek_num(StackType* s) { //������
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����");
		exit(1);
	}
	else return s->num[(s->top)];
}
int prec(char op) {
	switch (op) {
	case'(': return 0;
	case'|': return 1;
	case'&': return 2;
	case'>': case'<': case'=': return 3;
	case'+': case'-': return 4;
	case'*': case'/': case'%': return 5;
	case'^': return 6;
	}
	return -1;
}

int eval_postfix(char* str) { // ������ ���
	StackType s;
	init_stack(&s);
	int ch1, ch2, value;
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if (prec(str[i]) == -1) { // prec���� -1�� ��ȯ�Ǹ� ����
			value = str[i] - '0'; 
			printf("[ %d ] --- push\n\n", value);
			push_num(&s, value); // ���ÿ� ����
		}
		else { // �������� ��� ���ÿ� �ִ� �� 2���� ������ ����
			ch1 = pop_num(&s);
			printf("[ %d ] --- pop\n\n", ch1);
			ch2 = pop_num(&s);
			printf("[ %d ] --- pop\n\n", ch2);
			printf("[ %c ] --- ���ǽ� \n\n", str[i]);

			switch (str[i]) {
			case'+': {
				push_num(&s, ch2 + ch1);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, ch2 + ch1);
				break;
			}
			case'-': {
				push_num(&s, ch2 - ch1);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, ch2 - ch1);
				break;
			}
			case'*': {
				push_num(&s, ch2 * ch1);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, ch2 * ch1);
				break;
			}
			case'/': {
				push_num(&s, ch2 / ch1);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, ch2 / ch1);
				break;
			}
			case'%': {
				push_num(&s, ch2 % ch1);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, ch2 % ch1);
				break;
			}
			case'^': {
				int sum = 1;
				for (int i = 0; i < ch1; i++) sum *= ch2;
				push_num(&s, sum);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, sum);
				break;
			}
			case'>': {
				if (ch2 > ch1) push_num(&s, 1);
				else push_num(&s, 0);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, peek_num(&s));
				break;
			}
			case'<': {
				if (ch2 < ch1) push_num(&s, 1);
				else push_num(&s, 0);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, peek_num(&s));
				break;
			}
			case'=': {
				if (ch2 == ch1) push_num(&s, 1);
				else push_num(&s, 0);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, peek_num(&s));
				break;
			}
			case'&': {
				if (ch2 && ch1) push_num(&s, 1);
				else push_num(&s, 0);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, peek_num(&s));
				break;
			}
			case'|': {
				if (ch2 || ch1) push_num(&s, 1);
				else push_num(&s, 0);
				printf("[ %d %c %d ] result: %d  --- push\n\n", ch2, str[i], ch1, peek_num(&s));
				break;
			}
			}
		}

	}
	printf("-------------------------------------\n\n");
	return pop_num(&s);
}//34+2-222^*>73-2/52*&

void postfix(char* str) {
	char top_op;
	int len = strlen(str);

	char res[100] = { 0, }; // ��������� ����� �迭 (����ϱ� ���� �ٷ� ��� ���ϰ� ����)

	StackType s;
	init_stack(&s);

	int rindex = 0, sindex = 0;

	while (sindex < len) {
		if (str[sindex] == '(') { //������ȣ�� Ǫ��
			push(&s, str[sindex++]);
			printf("[ %c ] --- push\n\n", peek(&s));
			continue;
		}

		else if (str[sindex] == ')') {
			printf("---------���� ��ȣ ����---------\n\n");
			printf("[ %c ] --- pop\n\n", peek(&s));
			top_op = pop(&s);

			while (top_op != '(') { // ���� ��ȣ�� ���Ë����� �� �ǽ�
				res[rindex++] = top_op;
				printf("[ %c ] --- pop\n\n", peek(&s));
				top_op = pop(&s);
			}
			printf("-----���� ��ȣ���� POP �Ϸ�-----\n\n");
			sindex++;
			if (sindex >= len) break;
		}

		if (prec(str[sindex]) == -1) res[rindex++] = str[sindex++]; // �ǿ����ڸ� �迭�� ����

		else { // �������� ���
			
			if (is_empty(&s)) { // ������ ��� ������ ������ Ǫ��
				push(&s, str[sindex++]);
				printf("[ %c ] --- push\n\n", peek(&s));
			} 

			else if (prec(peek(&s)) < prec(str[sindex]) || (str[sindex] =='^' && peek(&s) == '^')) { // ���� �����ڰ� ���� ž ������ ���� �켱 ������ ������ Ǫ��
				push(&s, str[sindex++]);
				printf("[ %c ] --- push\n\n", peek(&s));
			}

			else { // ���� �����ڰ� ���ų� ������ �� �迭�� ����
				printf("[ %c ] --- pop\n\n", peek(&s));
				res[rindex++] = pop(&s);
			}
		}
	}
	while (!is_empty(&s)) { // ���ÿ� ���� ������ ��
		printf("[ %c ] --- pop\n\n", peek(&s));
		res[rindex++] = pop(&s);
	}
	printf("\n���������: %s\n\n", res);
	printf("\n��갪: %d", eval_postfix(res));
}

int main(void) {
	char str[100];
	printf("��������� �Է�: ");
	scanf("%s", str);
	postfix(str);
	return 0;
}

//3+4*(3+4)/2<6    3434+*2/+6<
//5+2&(3-1*2)|2^2^3>2*(2+1)     52+312*->223^^221+*>|   
//(2+1)^2^2>3+2+(3>2)   21+22^^32+32>+>
//(6-3*2)|2^2^3&(3<2+3)

/*
* (4+9-1)%(2+1)
* 3+2^3^2-1
* 3+4-2>2*3^2
* 3+4-2>2*2^2&(5-3)%2<5*2
*/