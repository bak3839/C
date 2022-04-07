#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 51
typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;
void init_stack(StackType* s) {
	s->top = -1;
}
int is_empty(StackType* s) { // 스택이 비어있는지 확인
	return (s->top == -1);
}
void push(StackType* s, element item) { // 스택에 값을 넣는 함수
	s->data[++(s->top)] = item;
}
void pop(StackType* s) { // 스택 탑 감소 및 출력
	--(s->top);
}
element peek(StackType* s) { // 탑에 있는 값 확인
	return s->data[(s->top)];
}
int cmp(char* str) {
	StackType s;
	init_stack(&s);
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		switch (str[i]) {
		case'(': {
			push(&s, str[i]);
			break;
		}
		case')': {
			if (is_empty(&s)) return 0;
			else pop(&s);
		}
		}
	}
	if (!is_empty(&s)) return 0;
	else return 1;
}
int main(void) {
	char ch[51];
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", ch);
		if (cmp(ch) == 1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}