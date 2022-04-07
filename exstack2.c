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
	case'&': case'|': return 0;
	case'>': case'<': case'=': return 1;
	case'+': case'-': return 2;
	case'*': case'/': return 3;
	case'^': return 4;
	}
	return -1;
}
void postfix(char *str) {
	char ch, top_op;
	int len = strlen(str);

	char* res = malloc(sizeof(char) * (len + 1));
	res[len] = '\0';

	StackType s;
	init_stack(&s);

	int rindex = 0, sindex = 0;

	while (rindex < len && sindex < len) {
		if (prec(str[sindex]) == -1) res[rindex++] = str[sindex++];
		else {
			if (is_empty(&s)) push(&s, str[sindex++]);
			else if (prec(peek(&s)) < prec(str[sindex])) push(&s, str[sindex++]);
			else {
				res[rindex++] = pop(&s);
			}
		}
	}
	for (int j = rindex; j < len; j++) res[j] = pop(&s);
	printf("%s", res);
	free(res);
}

int main(void) {
	char str[100];
	scanf("%s", str);
	postfix(str);
	return 0;
}