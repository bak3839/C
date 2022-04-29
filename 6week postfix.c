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

void push_num(StackType* s, int item) { // 정수형
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 오류");
		return;
	}
	else s->num[++(s->top)] = item;
}

element pop(StackType* s) { // 스택 탑 감소 및 출력
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 오류");
		exit(1);
	}
	else return s->data[(s->top)--];
}

int pop_num(StackType* s) { // 정수형
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 오류");
		exit(1);
	}
	else return s->num[(s->top)--];
}

element peek(StackType* s) { // 탑에 있는 값 확인
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 오류");
		exit(1);
	}
	else return s->data[(s->top)];
}

int peek_num(StackType* s) { //정수형
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 오류");
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

int eval_postfix(char* str) { // 후위식 계산
	StackType s;
	init_stack(&s);
	int ch1, ch2, value;
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if (prec(str[i]) == -1) { // prec에서 -1이 반환되면 숫자
			value = str[i] - '0'; 
			printf("[ %d ] --- push\n\n", value);
			push_num(&s, value); // 스택에 저장
		}
		else { // 연산자일 경우 스택에 있는 수 2개를 꺼내어 연산
			ch1 = pop_num(&s);
			printf("[ %d ] --- pop\n\n", ch1);
			ch2 = pop_num(&s);
			printf("[ %d ] --- pop\n\n", ch2);
			printf("[ %c ] --- 계산실시 \n\n", str[i]);

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

	char res[100] = { 0, }; // 후위연산식 저장용 배열 (계산하기 위해 바로 출력 안하고 저장)

	StackType s;
	init_stack(&s);

	int rindex = 0, sindex = 0;

	while (sindex < len) {
		if (str[sindex] == '(') { //열린괄호는 푸시
			push(&s, str[sindex++]);
			printf("[ %c ] --- push\n\n", peek(&s));
			continue;
		}

		else if (str[sindex] == ')') {
			printf("---------닫힌 괄호 등장---------\n\n");
			printf("[ %c ] --- pop\n\n", peek(&s));
			top_op = pop(&s);

			while (top_op != '(') { // 열린 괄호가 나올떄까지 팝 실시
				res[rindex++] = top_op;
				printf("[ %c ] --- pop\n\n", peek(&s));
				top_op = pop(&s);
			}
			printf("-----열린 괄호까지 POP 완료-----\n\n");
			sindex++;
			if (sindex >= len) break;
		}

		if (prec(str[sindex]) == -1) res[rindex++] = str[sindex++]; // 피연산자면 배열에 저장

		else { // 연산자일 경우
			
			if (is_empty(&s)) { // 스택이 비어 있으면 연산자 푸시
				push(&s, str[sindex++]);
				printf("[ %c ] --- push\n\n", peek(&s));
			} 

			else if (prec(peek(&s)) < prec(str[sindex]) || (str[sindex] =='^' && peek(&s) == '^')) { // 현재 연사자가 스택 탑 연산자 보다 우선 순위가 높으면 푸시
				push(&s, str[sindex++]);
				printf("[ %c ] --- push\n\n", peek(&s));
			}

			else { // 현재 연산자가 높거나 같으면 팝 배열에 저장
				printf("[ %c ] --- pop\n\n", peek(&s));
				res[rindex++] = pop(&s);
			}
		}
	}
	while (!is_empty(&s)) { // 스택에 남은 연산자 팝
		printf("[ %c ] --- pop\n\n", peek(&s));
		res[rindex++] = pop(&s);
	}
	printf("\n후위연산식: %s\n\n", res);
	printf("\n계산값: %d", eval_postfix(res));
}

int main(void) {
	char str[100];
	printf("중위연산식 입력: ");
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