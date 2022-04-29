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
int is_full(StackType* s) { // 스택이 가득 차있는지 확인
	return (s->top == (MAX_STACK_SIZE - 1));
}

int is_empty(StackType* s) { // 스택이 비어있는지 확인
	return (s->top == -1);
}

void push(StackType* s, element item) { // 스택에 값을 넣는 함수
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 오류");
		return;
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s) { // 스택 탑 감소 및 출력
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 오류");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) { // 탑에 있는 값 확인
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 오류");
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
			if (is_empty(&s)) push(&s, ch); //스택이 비어있다면 그냥 푸시

			else if (prec(peek(&s)) < prec(ch)) push(&s, ch); // 연산자 순위가 높으면 푸시

			else { // 연산자 순위가 같거나 작으면
				printf("%c", pop(&s));

				while (!is_empty(&s)) { // 스택에 쌓인 다른 연산자와 현재 연산자와 순위를 비교
					if (prec(peek(&s)) >= prec(ch)) printf("%c", pop(&s)); // 스택에 있는 연산자의 순위가 높으면 팝
					else break; // 아니면 탈출
				}

				push(&s, ch); // 현재 연산자를 푸시
			}
		}
	}
	while (!is_empty(&s)) { // 스택에 남아있는 연산자를 출력
		printf("%c", pop(&s));
	}
}

int main(void) {
	char str[100];
	scanf("%s", str);
	postfix(str);
	return 0;
}