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