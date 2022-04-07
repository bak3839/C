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
void cmp(char *ch) {
	StackType s;
	StackType n; // 번호 출력용
	init_stack(&s);
	init_stack(&n);
	char a = '0';
	int len = strlen(ch);
	char open_ch;
	for (int i = 0; i < len; i++) {
		switch (ch[i]) {
		case'(': case'{': case'[': {
			push(&n, ++a); // 번호 1증가 스택에 넣기
			push(&s, ch[i]); // 열린 괄호 스택에 넣기
			printf("%c ", peek(&n)); // 번호 출력
			break;
		}

		case')': case'}': case']': {
			if (is_empty(&s)) {
				printf("\n남은 열린 괄호가 없습니다.");
				return 0;
			} // 닫힌 괄호가 나왔지만 남은 열린괄호가 없으면 종료
			else {
				open_ch = pop(&s);// 괄호의 짝이 맞는지 판별
				if (open_ch == '(' && ch[i] != ')' ||
					open_ch == '{' && ch[i] != '}' ||
					open_ch == '[' && ch[i] != ']'){
					printf("\n괄호의 짝이 맞지 않습니다");
					return 0;
				}
				else printf("%c ", pop(&n)); // 쌓여있던 번호 출력
			}
			break;
		}
		}
	}
	if (!is_empty(&s)) printf("\n열린 괄호가 남았습니다.");
		
}

int main(void) {
	char str[100];
	printf("문자 입력:");
	scanf("%s", str);
	cmp(str);
	return 0;
}