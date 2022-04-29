#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX 10

typedef struct {
	short r;
	short c;
} element;


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
void print(char maze[MAX][MAX]) {
	printf("\n");
	for (int r = 0; r < MAX; r++) {
		for (int c = 0; c < MAX; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}
char maze[MAX][MAX] = {
	{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{ 'e', '0', '0', '1', '1', '0', '0', '0', '1', '1'},
	{ '1', '1', '0', '0', '0', '0', '1', '0', '0', '0'},
	{ '1', '1', '0', '1', '1', '1', '1', '1', '1', '0'},
	{ '1', '1', '0', '0', '0', '0', '0', '0', '0', 'x'},
	{ '1', '1', '0', '1', '1', '1', '1', '1', '1', '0'},
	{ '1', '1', '0', '0', '0', '1', '1', '1', '1', '0'},
	{ '1', '1', '1', '1', '0', '1', '1', '0', '0', '0'},
	{ '1', '1', '0', '0', '0', '0', '0', '0', '1', '0'},
	{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};
void location(StackType* s, int r, int c) {
	if (r < 0 || c < 0 || r >= MAX || c >= MAX) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element res;
		res.r = r;
		res.c = c;
		printf("                 PUSH [ %d , %d ]\n\n", r, c);
		push(s, res);
	}
}
element here = { 1,0 };
int main(viod) {
	StackType s;
	init_stack(&s);
	int r, c;

	while (1) {
		printf("( %d , %d )\n\n", here.r, here.c);
		printf("    |\n");
		printf("    V\n");
		while (maze[here.r][here.c] != 'x') {
			r = here.r;
			c = here.c;
			maze[r][c] = '.';
			// 탐색순서는 위 -> 아래 -> 좌 -> 우

			// 진입순서는 우 -> 좌 -> 아래 -> 위

			location(&s, r - 1, c); // 위
			location(&s, r + 1, c); // 아래
			location(&s, r, c - 1); // 좌
			location(&s, r, c + 1); // 우

			if (is_empty(&s)) {
				printf("길이 없습니다.\n");
				return 0;
			}

			else {
				here = pop(&s);
				printf("( %d , %d )\n\n", here.r, here.c);
				printf("    |\n");
				printf("    V\n\n");
			}
		}
		printf("\n--------출구 도착!!!--------\n\n");

		if (!is_empty(&s)) {
			printf("-----새로운길 탐색 시작-----\n\n");
			here = pop(&s);
		}
		else break;
	}
	return 0;
}