#include <stdio.h>
#include <Stdlib.h>
#define MAX 100

typedef char* element;

typedef struct {
	element data[MAX];
	int rear, front;
}QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) { // 큐 초기화
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) { // 큐가 비어있는지 확인
	return (q->front == q->rear);
}

int is_full(QueueType* q) { // 큐가 포화 상태인지 확인
	return ((q->rear + 1) % MAX == q->front);
}

void enqueue(QueueType* q, element item) { // 큐 삽입
	if (is_full(q))
		error("큐 포화");
	q->rear = (q->rear + 1) % MAX;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) { // 큐 삭제
	if (is_empty(q))
		error("큐 공백");
	q->front = (q->front + 1) % MAX;
	return q->data[q->front];
}

element peek(QueueType* q) { // 큐 확인
	if (is_empty(q))
		error("큐 공백");
	return q->data[(q->front + 1) % MAX];
}

void matching(QueueType* boy, QueueType* girl) {
	if (is_empty(boy) || is_empty(girl)) {
		printf("-- 대기\n");
	}
	else {
		element b = dequeue(boy);
		element g = dequeue(girl);
		printf("-- %s / %s 매칭\n", b, g);
	}
}
int main(void) {
	QueueType boy;
	QueueType girl;

	init_queue(&boy);
	init_queue(&girl);

	int b_num = 0, g_num = 0;

	for (int i = 0; i < 15; i++) {
		int random = rand() % 2;
		element e;
		if (random == 1) { // 남
			printf("남%d 입장", ++b_num);
			sprintf(&e, "남%d", b_num);
			enqueue(&boy, &e);
			matching(&boy, &girl);
		}
		else {
			printf("여%d 입장", ++g_num);
			sprintf(&e, "여%d", g_num);
			enqueue(&girl, &e);
			matching(&boy, &girl);
		}
	}
	return 0;
}