#include <stdio.h>
#include <Stdlib.h>
#define MAX 100

typedef int element;

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

int main(void) {
	QueueType f;
	init_queue(&f);

	enqueue(&f, 0);
	enqueue(&f, 1);

	int n;
	printf("피보나치 순서 입력:");
	scanf("%d", &n);

	for (int i = 2; i < n; i++) {
		int sum = dequeue(&f) + peek(&f);
		enqueue(&f, sum);
	}
	printf("%d번째 값:%d", n, dequeue(&f) + dequeue(&f));
	return 0;
}