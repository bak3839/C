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

element peek(StackType* s) { // 탑에 있는 값 확인
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 오류");
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
	printf("문자열 입력: ");
	gets(str);
	run_length(str);
	return 0;
}