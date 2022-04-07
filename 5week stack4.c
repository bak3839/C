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
	switch (op) { // 문자인지 연산자인지 판별
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
		if (prec(str[i]) == -1) { // prec에서 -1이 반환되면 숫자
			value = str[i] - '0'; // 정수형으로 바꿔서 저장
			printf("< %d > --- push\n\n", value);
			push(&s, value); // 스택에 저장
		}
		else { // 연산자일 경우 스택에 있는 수 2개를 꺼내어 연산
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
	printf("후위 연산식 입력: ");
	scanf("%s", str);
	printf(" ----연산 결과: %d----", calstr(str));
	return 0;
}